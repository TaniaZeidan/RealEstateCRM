#ifndef CONTRACT_H
#define CONTRACT_H

#include <iostream>
#include <string>
#include "Exceptions.h"

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
    std::string getStartDate() const;
    std::string getEndDate() const;
    std::string getContractType() const;
    bool getIsActive() const;

    // Setters
    void setId(int id);
    void setPropertyId(int propertyId);
    void setClientId(int clientId);
    void setAgentId(int agentId);
    void setPrice(double price);
    void setStartDate(const std::string &startDate);
    void setEndDate(const std::string &endDate);
    void setContractType(const std::string &contractType); // Must be "sale" or "rent"
    void setIsActive(bool isActive);

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
    std::string m_startDate;
    std::string m_endDate;
    std::string m_contractType; // "sale" or "rent"
    bool m_isActive;
};

#endif // CONTRACT_H
