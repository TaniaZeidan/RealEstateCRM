#include "Date.h"
#include <iomanip>
#include <sstream>
#include <ctime>

Date::Date() : m_isEmpty(false) {
    // Get current date
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    
    m_year = now->tm_year + 1900;
    m_month = now->tm_mon + 1;
    m_day = now->tm_mday;
}

Date::Date(int year, int month, int day)
    : m_year(year), m_month(month), m_day(day), m_isEmpty(false) {
    validate();
}

Date::Date(const std::string& dateStr) : m_isEmpty(false) {
    if (dateStr.empty()) {
        m_isEmpty = true;
        m_year = 0;
        m_month = 0;
        m_day = 0;
        return;
    }
    
   try {
        if (dateStr.find('-') != std::string::npos) {
            // Parse "YYYY-MM-DD" format with hyphens
            std::stringstream ss(dateStr);
            char delimiter;
            ss >> m_year >> delimiter >> m_month >> delimiter >> m_day;
            
            if (ss.fail()) {
                throw std::invalid_argument("Invalid date format");
            }
        } else if (dateStr.length() == 8) {
            // Parse as YYYYMMDD
            m_year = std::stoi(dateStr.substr(0, 4));
            m_month = std::stoi(dateStr.substr(4, 2));
            m_day = std::stoi(dateStr.substr(6, 2));
        } else {
            throw std::invalid_argument("Invalid date format");
        }
        
        validate();
    } catch (const std::exception&) {
        throw InvalidDateException(dateStr);
    }
}

std::string Date::toString() const {
    if (m_isEmpty) {
        return "";
    }
    
    std::stringstream ss;
    ss << std::setw(4) << std::setfill('0') << m_year << "-"
       << std::setw(2) << std::setfill('0') << m_month << "-"
       << std::setw(2) << std::setfill('0') << m_day;
    return ss.str();
}

bool Date::isValid(int year, int month, int day) {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > daysInMonth(year, month)) return false;
    return true;
}

void Date::validate() const {
    if (m_isEmpty) return;
    
    if (!isValid(m_year, m_month, m_day)) {
        throw InvalidDateException(toString());
    }
}

bool Date::operator==(const Date& other) const {
    if (m_isEmpty && other.m_isEmpty) return true;
    if (m_isEmpty || other.m_isEmpty) return false;
    
    return m_year == other.m_year && m_month == other.m_month && m_day == other.m_day;
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

bool Date::operator<(const Date& other) const {
    if (m_isEmpty) return !other.m_isEmpty; // Empty dates are "less than" non-empty dates
    if (other.m_isEmpty) return false;
    
    if (m_year != other.m_year) return m_year < other.m_year;
    if (m_month != other.m_month) return m_month < other.m_month;
    return m_day < other.m_day;
}

bool Date::operator<=(const Date& other) const {
    return *this < other || *this == other;
}

bool Date::operator>(const Date& other) const {
    return !(*this <= other);
}

bool Date::operator>=(const Date& other) const {
    return !(*this < other);
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.toString();
    return os;
}

std::istream& operator>>(std::istream& is, Date& date) {
    std::string dateStr;
    is >> dateStr;
    try {
        date = Date(dateStr);
    } catch (const InvalidDateException&) {
        is.setstate(std::ios::failbit);
    }
    return is;
}

bool Date::isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Date::daysInMonth(int year, int month) {
    static const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return days[month - 1];
}

Date Date::fromString(const std::string& dateStr) {
    if (dateStr.empty()) {
        return emptyDate();
    }
    return Date(dateStr);
}

bool Date::isEmpty() const {
    return m_isEmpty;
}

Date Date::emptyDate() {
    Date date;
    date.m_isEmpty = true;
    date.m_year = 0;
    date.m_month = 0;
    date.m_day = 0;
    return date;
}