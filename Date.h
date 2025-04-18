#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>
#include "Exceptions.h"

class Date {
public:
    // Constructors
    Date(); // Current date
    Date(int year, int month, int day);
    Date(const std::string& dateStr); // Format: "YYYY-MM-DD"
    
    // Getters
    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const { return m_day; }
    
    // Convert to string in "YYYY-MM-DD" format
    std::string toString() const;
    
    // Check if date is valid
    static bool isValid(int year, int month, int day);
    
    // Compare dates
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator>=(const Date& other) const;
    
    // Stream operators
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    friend std::istream& operator>>(std::istream& is, Date& date);
    
    // Static methods for validation
    static bool isLeapYear(int year);
    static int daysInMonth(int year, int month);
    
    // Parse string to Date
    static Date fromString(const std::string& dateStr);
    
    // Check if date is empty (for optional dates)
    bool isEmpty() const;
    
    // Create an empty date
    static Date emptyDate();

private:
    int m_year;
    int m_month;
    int m_day;
    bool m_isEmpty;
    
    void validate() const;
};

#endif