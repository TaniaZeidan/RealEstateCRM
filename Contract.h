#ifndef CONTRACT_H
#define CONTRACT_H

#include <iostream>
#include <string>
#include "Exceptions.h"
#include "Date.h"

class Contract {
public:
    Contract();
    Contract(int id, int propertyId, int clientId, int agentId,
             double price, const std::string &startDate, const std::string &endDate,
             const std::string &contractType, bool isActive);

    // Getters
    int getId() const;
    int getPropertyId() const;
    int getClientId() const;
    int getAgentId() const;
    double getPrice() const;
    Date getStartDate() const;
    Date getEndDate() const;
    std::string getContractType() const;
    bool getIsActive() const;

    // Setters
    void setId(int id);
    void setPropertyId(int propertyId);
    void setClientId(int clientId);
    void setAgentId(int agentId);
    void setPrice(double price);
    void setStartDate(const Date &startDate);
    void setEndDate(const Date &endDate);
    void setContractType(const std::string &contractType); // Must be "sale" or "rent"
    void setIsActive(bool isActive);

    // For backward compatibility (used in file operations)
    std::string getStartDateString() const;
    std::string getEndDateString() const;
    void setStartDateFromString(const std::string& startDate);
    void setEndDateFromString(const std::string& endDate);

    // Validation
    bool isValid() const;

    // Overloaded stream operators
    friend std::ostream& operator<<(std::ostream &os, const Contract &contract);
    friend std::istream& operator>>(std::istream &is, Contract &contract);

private:
    int m_id;
    int m_propertyId;
    int m_clientId;
    int m_agentId;
    double m_price;
    Date m_startDate;
    Date m_endDate;
    std::string m_contractType; // "sale" or "rent"
    bool m_isActive;
};

#endif // CONTRACT_H
