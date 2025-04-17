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
std::string Contract::getStartDate() const { return m_startDate; }
std::string Contract::getEndDate() const { return m_endDate; }
std::string Contract::getContractType() const { return m_contractType; }
bool Contract::getIsActive() const { return m_isActive; }

void Contract::setId(int id) { m_id = id; }
void Contract::setPropertyId(int propertyId) { m_propertyId = propertyId; }
void Contract::setClientId(int clientId) { m_clientId = clientId; }
void Contract::setAgentId(int agentId) { m_agentId = agentId; }
void Contract::setPrice(double price) { m_price = price; }
void Contract::setStartDate(const std::string &startDate) { m_startDate = startDate; }
void Contract::setEndDate(const std::string &endDate) { m_endDate = endDate; }
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
    if(m_startDate.empty()) 
        return false;
    if(!m_endDate.empty() && m_startDate > m_endDate) 
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
