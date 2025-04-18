#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <string>
#include "Exceptions.h"
#include "Date.h"

class Agent {
public:
    Agent();
    Agent(int id, const std::string &firstName, const std::string &lastName,
          const std::string &phone, const std::string &email,
          const std::string &startDate, const std::string &endDate);

    // Getters
    int getId() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPhone() const;
    std::string getEmail() const;
    Date getStartDate() const;
    Date getEndDate() const;

    // Setters
    void setId(int id);
    void setFirstName(const std::string &firstName);
    void setLastName(const std::string &lastName);
    void setPhone(const std::string &phone);
    void setEmail(const std::string &email);
    void setStartDate(const Date &startDate);
    void setEndDate(const Date &endDate);

    // For backward compatibility (used in file operations)
    std::string getStartDateString() const;
    std::string getEndDateString() const;
    void setStartDateFromString(const std::string& startDate);
    void setEndDateFromString(const std::string& endDate);

    // Basic validation
    bool isValid() const;

    // Overloaded operators for streaming (<<, >>)
    friend std::ostream& operator<<(std::ostream &os, const Agent &agent);
    friend std::istream& operator>>(std::istream &is, Agent &agent);

private:
    int m_id;  
    std::string m_firstName;
    std::string m_lastName;
    std::string m_phone;
    std::string m_email;
    Date m_startDate; // e.g., "YYYY-MM-DD"
    Date m_endDate;   // e.g., "YYYY-MM-DD" or empty
};

#endif // AGENT_H
