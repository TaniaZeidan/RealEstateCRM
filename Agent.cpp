#include "Agent.h"
#include <sstream>

Agent::Agent() : m_id(-1) {}

Agent::Agent(int id, const std::string &firstName, const std::string &lastName,
             const std::string &phone, const std::string &email,
             const std::string &startDate, const std::string &endDate)
    : m_id(id), m_firstName(firstName), m_lastName(lastName),
      m_phone(phone), m_email(email)
{
    setStartDateFromString(startDate);
    setEndDateFromString(endDate);
}

int Agent::getId() const { return m_id; }
std::string Agent::getFirstName() const { return m_firstName; }
std::string Agent::getLastName() const { return m_lastName; }
std::string Agent::getPhone() const { return m_phone; }
std::string Agent::getEmail() const { return m_email; }
Date Agent::getStartDate() const { return m_startDate; }
Date Agent::getEndDate() const { return m_endDate; }

void Agent::setId(int id) { m_id = id; }
void Agent::setFirstName(const std::string &firstName) { m_firstName = firstName; }
void Agent::setLastName(const std::string &lastName) { m_lastName = lastName; }
void Agent::setPhone(const std::string &phone) { m_phone = phone; }
void Agent::setEmail(const std::string &email) { m_email = email; }
void Agent::setStartDate(const Date &startDate) { m_startDate = startDate; }
void Agent::setEndDate(const Date &endDate) { 
    m_endDate = endDate;
    
    // Validate that end date is after start date if both are not empty
    if (!m_startDate.isEmpty() && !m_endDate.isEmpty() && m_endDate < m_startDate) {
        throw InvalidDateRangeException(m_startDate.toString(), m_endDate.toString());
    }
}

std::string Agent::getStartDateString() const { return m_startDate.toString(); }
std::string Agent::getEndDateString() const { 
    if (m_endDate.isEmpty()) {
        return "";
    }
    return m_endDate.toString(); 
}

void Agent::setStartDateFromString(const std::string& startDate) {
    try {
        m_startDate = Date(startDate);
    } catch (const InvalidDateException& e) {
        throw ValidationException("Invalid start date: " + startDate);
    }
}

void Agent::setEndDateFromString(const std::string& endDate) {
    if (endDate.empty()) {
        m_endDate = Date::emptyDate();
    } else {
        try {
            m_endDate = Date(endDate);
            
            // Validate that end date is after start date
            if (!m_startDate.isEmpty() && !m_endDate.isEmpty() && m_endDate < m_startDate) {
                throw InvalidDateRangeException(m_startDate.toString(), m_endDate.toString());
            }
        } catch (const InvalidDateException& e) {
            throw ValidationException("Invalid end date: " + endDate);
        }
    }
}

bool Agent::isValid() const {
    // Basic field validations
    if(m_firstName.empty() || m_lastName.empty()) 
        return false;
    if(m_email.find('@') == std::string::npos) 
        return false;
    
    // StartDate must always be valid (not empty)
    if(m_startDate.isEmpty())
        return false;
    
    // If end date is not empty, it must be after start date
    if(!m_endDate.isEmpty() && m_endDate < m_startDate)
        return false;
        
    return true;
}

std::ostream& operator<<(std::ostream &os, const Agent &agent) {
    os << "ID: " << agent.m_id 
       << "\nName: " << agent.m_firstName << " " << agent.m_lastName
       << "\nPhone: " << agent.m_phone 
       << "\nEmail: " << agent.m_email
       << "\nStart: " << agent.m_startDate
       << "\nEnd: " << agent.m_endDate;
    return os;
}

std::istream& operator>>(std::istream &is, Agent &agent) {
    // Simple space-separated read (not heavily used in the final code, but provided for completeness)
    is >> agent.m_id >> agent.m_firstName >> agent.m_lastName >> agent.m_phone
       >> agent.m_email >> agent.m_startDate >> agent.m_endDate;
    return is;
}
