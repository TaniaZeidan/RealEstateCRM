#include "Contract.h"
#include "Exceptions.h"
#include <stdexcept>

Contract::Contract() 
    : m_id(-1), m_propertyId(-1), m_clientId(-1), m_agentId(-1), m_price(0.0), m_isActive(false), m_contractType("rent")
{}

Contract::Contract(int id, int propertyId, int clientId, int agentId,
                   double price, const std::string &startDate, const std::string &endDate,
                   const std::string &contractType, bool isActive)
    : m_id(id), m_propertyId(propertyId), m_clientId(clientId), m_agentId(agentId),
      m_price(price), m_startDate(startDate), m_endDate(endDate), m_isActive(isActive)
{
    setContractType(contractType);
}

int Contract::getId() const { return m_id; }
int Contract::getPropertyId() const { return m_propertyId; }
int Contract::getClientId() const { return m_clientId; }
int Contract::getAgentId() const { return m_agentId; }
double Contract::getPrice() const { return m_price; }
Date Contract::getStartDate() const { return m_startDate; }
Date Contract::getEndDate() const { return m_endDate; }
std::string Contract::getContractType() const { return m_contractType; }
bool Contract::getIsActive() const { return m_isActive; }

void Contract::setId(int id) { m_id = id; }
void Contract::setPropertyId(int propertyId) { m_propertyId = propertyId; }
void Contract::setClientId(int clientId) { m_clientId = clientId; }
void Contract::setAgentId(int agentId) { m_agentId = agentId; }
void Contract::setPrice(double price) { m_price = price; }
void Contract::setStartDate(const Date &startDate) { m_startDate = startDate; }
void Contract::setEndDate(const Date &endDate) { m_endDate = endDate; }

std::string Contract::getStartDateString() const { return m_startDate.toString(); }
std::string Contract::getEndDateString() const { return m_endDate.toString(); }

void Contract::setStartDateFromString(const std::string& startDate) {
    try {
        m_startDate = Date(startDate);
    } catch (const InvalidDateException& e) {
        throw ValidationException("Invalid start date: " + startDate);
    }
}

void Contract::setEndDateFromString(const std::string& endDate) {
    if (endDate.empty()) {
        m_endDate = Date::emptyDate();
    } else {
        try {
            m_endDate = Date(endDate);
            
            // Validate that end date is after start date for rental contracts
            if (m_contractType == "rent" && !m_startDate.isEmpty() && m_endDate < m_startDate) {
                throw InvalidDateRangeException(m_startDate.toString(), m_endDate.toString());
            }
        } catch (const InvalidDateException& e) {
            throw ValidationException("Invalid end date: " + endDate);
        }
    }
}

void Contract::setContractType(const std::string &contractType) {
    if(contractType != "sale" && contractType != "rent")
        throw ValidationException("Contract type must be 'sale' or 'rent'.");
    m_contractType = contractType;
}
void Contract::setIsActive(bool isActive) { m_isActive = isActive; }

bool Contract::isValid() const {
    if(m_propertyId < 0 || m_clientId < 0 || m_agentId < 0) 
        return false;
    if(m_price < 0) 
        return false;
    if(m_startDate.isEmpty())
        return false;
    if(!m_endDate.isEmpty() && m_startDate > m_endDate) 
        return false;
    if(m_contractType != "sale" && m_contractType != "rent") 
        return false;
    return true;
}

std::ostream& operator<<(std::ostream &os, const Contract &contract) {
    os << "ID: " << contract.m_id
       << "\nPropertyID: " << contract.m_propertyId
       << "\nClientID: " << contract.m_clientId
       << "\nAgentID: " << contract.m_agentId
       << "\nPrice: " << contract.m_price
       << "\nStart: " << contract.m_startDate
       << "\nEnd: " << contract.m_endDate
       << "\nType: " << contract.m_contractType
       << "\nActive: " << (contract.m_isActive ? "Yes" : "No");
    return os;
}

std::istream& operator>>(std::istream &is, Contract &contract) {
    // Order: id, propertyId, clientId, agentId, price, startDate, endDate, contractType, isActive (0/1)
    int active;
    is >> contract.m_id >> contract.m_propertyId >> contract.m_clientId >> contract.m_agentId
       >> contract.m_price >> contract.m_startDate >> contract.m_endDate >> contract.m_contractType >> active;
    contract.m_isActive = (active != 0);
    return is;
}
