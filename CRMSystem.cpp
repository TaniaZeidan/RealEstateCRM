#include "CRMSystem.h"
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <iostream>

// Helper function to split CSV line
static std::vector<std::string> splitCSV(const std::string &line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    return tokens;
}

CRMSystem::CRMSystem() : nextAgentId(1), nextClientId(1), nextPropertyId(1), nextContractId(1) {
    loadData();
}

CRMSystem::~CRMSystem() {
    saveData();
}

// ------------------------
// Agent CRUD
// ------------------------
void CRMSystem::addAgent(const Agent &agent) {
    Agent a = agent;
    if (a.getId() == -1) {
        a.setId(nextAgentId++);
    }
    if (!a.isValid())
        throw std::invalid_argument("Invalid agent data.");
    agents.push_back(a);
}

bool CRMSystem::removeAgent(int agentId) {
    auto it = std::remove_if(agents.begin(), agents.end(),
                             [agentId](const Agent &a){ return a.getId() == agentId; });
    if(it != agents.end()) {
        agents.erase(it, agents.end());
        return true;
    }
    return false;
}

Agent CRMSystem::searchAgentById(int agentId) const {
    for(const auto &a : agents) {
        if(a.getId() == agentId)
            return a;
    }
    throw std::runtime_error("Agent not found.");
}

bool CRMSystem::modifyAgent(const Agent &modifiedAgent) {
    for(auto &a : agents) {
        if(a.getId() == modifiedAgent.getId()) {
            a = modifiedAgent;
            return true;
        }
    }
    return false;
}

void CRMSystem::displayAgents() const {
    if(agents.empty()) {
        std::cout << "No agents in the system.\n";
        return;
    }
    for(const auto &a : agents) {
        std::cout << a << "\n";
    }
}

// ------------------------
// Client CRUD
// ------------------------
void CRMSystem::addClient(const Client &client) {
    Client c = client;
    if(c.getId() == -1) {
        c.setId(nextClientId++);
    }
    if(!c.isValid())
        throw std::invalid_argument("Invalid client data.");
    clients.push_back(c);
}

bool CRMSystem::removeClient(int clientId) {
    auto it = std::remove_if(clients.begin(), clients.end(),
                             [clientId](const Client &c){ return c.getId() == clientId; });
    if(it != clients.end()) {
        clients.erase(it, clients.end());
        return true;
    }
    return false;
}

Client CRMSystem::searchClientById(int clientId) const {
    for(const auto &c : clients) {
        if(c.getId() == clientId)
            return c;
    }
    throw std::runtime_error("Client not found.");
}

bool CRMSystem::modifyClient(const Client &modifiedClient) {
    for(auto &c : clients) {
        if(c.getId() == modifiedClient.getId()) {
            c = modifiedClient;
            return true;
        }
    }
    return false;
}

void CRMSystem::displayClients() const {
    if(clients.empty()) {
        std::cout << "No clients in the system.\n";
        return;
    }
    for(const auto &c : clients) {
        std::cout << c << "\n";
    }
}

// ------------------------
// Property CRUD
// ------------------------
void CRMSystem::addProperty(const Property &property) {
    Property p = property;
    if(p.getId() == -1) {
        p.setId(nextPropertyId++);
    }
    if(!p.isValid())
        throw std::invalid_argument("Invalid property data.");
    properties.push_back(p);
}

bool CRMSystem::removeProperty(int propertyId) {
    auto it = std::remove_if(properties.begin(), properties.end(),
                             [propertyId](const Property &p){ return p.getId() == propertyId; });
    if(it != properties.end()) {
        properties.erase(it, properties.end());
        return true;
    }
    return false;
}

Property CRMSystem::searchPropertyById(int propertyId) const {
    for(const auto &p : properties) {
        if(p.getId() == propertyId)
            return p;
    }
    throw std::runtime_error("Property not found.");
}

bool CRMSystem::modifyProperty(const Property &modifiedProperty) {
    for(auto &p : properties) {
        if(p.getId() == modifiedProperty.getId()) {
            p = modifiedProperty;
            return true;
        }
    }
    return false;
}

void CRMSystem::displayProperties() const {
    if(properties.empty()) {
        std::cout << "No properties in the system.\n";
        return;
    }
    for(const auto &p : properties) {
        std::cout << p << "\n";
    }
}

// ------------------------
// Contract CRUD
// ------------------------
void CRMSystem::addContract(const Contract &contract) {
    Contract ct = contract;
    if(ct.getId() == -1) {
        ct.setId(nextContractId++);
    }
    if(!ct.isValid())
        throw std::invalid_argument("Invalid contract data.");
    contracts.push_back(ct);
}

bool CRMSystem::removeContract(int contractId) {
    auto it = std::remove_if(contracts.begin(), contracts.end(),
                             [contractId](const Contract &c){ return c.getId() == contractId; });
    if(it != contracts.end()) {
        contracts.erase(it, contracts.end());
        return true;
    }
    return false;
}

Contract CRMSystem::searchContractById(int contractId) const {
    for(const auto &c : contracts) {
        if(c.getId() == contractId)
            return c;
    }
    throw std::runtime_error("Contract not found.");
}

bool CRMSystem::modifyContract(const Contract &modifiedContract) {
    for(auto &c : contracts) {
        if(c.getId() == modifiedContract.getId()) {
            c = modifiedContract;
            return true;
        }
    }
    return false;
}

void CRMSystem::displayContracts() const {
    if(contracts.empty()) {
        std::cout << "No contracts in the system.\n";
        return;
    }
    for(const auto &c : contracts) {
        std::cout << c << "\n";
    }
}

// Create contract from existing records
void CRMSystem::createContract(int /*ignored*/, int propertyId, int clientId, int agentId,
                               double price, const std::string &startDate,
                               const std::string &endDate, const std::string &contractType, bool isActive)
{
    // Validate references first (will throw if not found)
    searchAgentById(agentId);
    searchClientById(clientId);
    searchPropertyById(propertyId);

    Contract contract(-1, propertyId, clientId, agentId, price, startDate, endDate, contractType, isActive);
    addContract(contract);
}

// ------------------------
// File Persistence
// ------------------------
void CRMSystem::loadData() {
    loadAgents();
    loadClients();
    loadProperties();
    loadContracts();
}

void CRMSystem::saveData() {
    saveAgents();
    saveClients();
    saveProperties();
    saveContracts();
}

void CRMSystem::loadAgents() {
    std::ifstream in("agents_data.csv");
    int maxId = 0;
    if(!in) return;
    std::string line;
    while(std::getline(in, line)) {
        if(line.empty()) continue;
        auto tokens = splitCSV(line);
        // Expected 7 tokens: id,firstName,lastName,phone,email,startDate,endDate
        if(tokens.size() < 7) continue;
        Agent a;
        a.setId(std::stoi(tokens[0]));
        if(a.getId() > maxId) maxId = a.getId();
        a.setFirstName(tokens[1]);
        a.setLastName(tokens[2]);
        a.setPhone(tokens[3]);
        a.setEmail(tokens[4]);
        a.setStartDate(tokens[5]);
        a.setEndDate(tokens[6]);
        agents.push_back(a);
    }
    in.close();
    nextAgentId = maxId + 1;
}

void CRMSystem::saveAgents() {
    std::ofstream out("agents_data.csv");
    for(const auto &a : agents) {
        out << a.getId() << ","
            << a.getFirstName() << ","
            << a.getLastName() << ","
            << a.getPhone() << ","
            << a.getEmail() << ","
            << a.getStartDate() << ","
            << a.getEndDate() << "\n";
    }
    out.close();
}

void CRMSystem::loadClients() {
    std::ifstream in("clients_data.csv");
    int maxId = 0;
    if(!in) return;
    std::string line;
    while(std::getline(in, line)) {
        if(line.empty()) continue;
        auto tokens = splitCSV(line);
        // Expected 8 tokens: id,firstName,lastName,phone,email,isMarried,budget,budgetType
        if(tokens.size() < 8) continue;
        Client c;
        c.setId(std::stoi(tokens[0]));
        if(c.getId() > maxId) maxId = c.getId();
        c.setFirstName(tokens[1]);
        c.setLastName(tokens[2]);
        c.setPhone(tokens[3]);
        c.setEmail(tokens[4]);
        bool married = (std::stoi(tokens[5]) != 0);
        c.setIsMarried(married);
        c.setBudget(std::stod(tokens[6]));
        c.setBudgetType(tokens[7]);
        clients.push_back(c);
    }
    in.close();
    nextClientId = maxId + 1;
}

void CRMSystem::saveClients() {
    std::ofstream out("clients_data.csv");
    for(const auto &c : clients) {
        out << c.getId() << ","
            << c.getFirstName() << ","
            << c.getLastName() << ","
            << c.getPhone() << ","
            << c.getEmail() << ","
            << (c.getIsMarried() ? 1 : 0) << ","
            << c.getBudget() << ","
            << c.getBudgetType() << "\n";
    }
    out.close();
}

void CRMSystem::loadProperties() {
    std::ifstream in("properties_data.csv");
    int maxId = 0;
    if(!in) return;
    std::string line;
    while(std::getline(in, line)) {
        if(line.empty()) continue;
        auto tokens = splitCSV(line);
        // Expected 9 tokens: id,sizeSqm,price,propertyType,bedrooms,bathrooms,place,available,listingType
        if(tokens.size() < 9) continue;
        Property p;
        p.setId(std::stoi(tokens[0]));
        if(p.getId() > maxId) maxId = p.getId();
        p.setSizeSqm(std::stod(tokens[1]));
        p.setPrice(std::stod(tokens[2]));
        p.setPropertyType(tokens[3]);
        p.setBedrooms(std::stoi(tokens[4]));
        p.setBathrooms(std::stoi(tokens[5]));
        p.setPlace(tokens[6]);
        p.setAvailability(std::stoi(tokens[7]) != 0);
        p.setListingType(tokens[8]);
        properties.push_back(p);
    }
    in.close();
    nextPropertyId = maxId + 1;
}

void CRMSystem::saveProperties() {
    std::ofstream out("properties_data.csv");
    for(const auto &p : properties) {
        out << p.getId() << ","
            << p.getSizeSqm() << ","
            << p.getPrice() << ","
            << p.getPropertyType() << ","
            << p.getBedrooms() << ","
            << p.getBathrooms() << ","
            << p.getPlace() << ","
            << (p.getAvailability() ? 1 : 0) << ","
            << p.getListingType() << "\n";
    }
    out.close();
}

void CRMSystem::loadContracts() {
    std::ifstream in("contracts_data.csv");
    int maxId = 0;
    if(!in) return;
    std::string line;
    while(std::getline(in, line)) {
        if(line.empty()) continue;
        auto tokens = splitCSV(line);
        // Expected 9 tokens: id,propertyId,clientId,agentId,price,startDate,endDate,contractType,isActive
        if(tokens.size() < 9) continue;
        Contract ct;
        ct.setId(std::stoi(tokens[0]));
        if(ct.getId() > maxId) maxId = ct.getId();
        ct.setPropertyId(std::stoi(tokens[1]));
        ct.setClientId(std::stoi(tokens[2]));
        ct.setAgentId(std::stoi(tokens[3]));
        ct.setPrice(std::stod(tokens[4]));
        ct.setStartDate(tokens[5]);
        ct.setEndDate(tokens[6]);
        ct.setContractType(tokens[7]);
        ct.setIsActive(std::stoi(tokens[8]) != 0);
        contracts.push_back(ct);
    }
    in.close();
    nextContractId = maxId + 1;
}

void CRMSystem::saveContracts() {
    std::ofstream out("contracts_data.csv");
    for(const auto &c : contracts) {
        out << c.getId() << ","
            << c.getPropertyId() << ","
            << c.getClientId() << ","
            << c.getAgentId() << ","
            << c.getPrice() << ","
            << c.getStartDate() << ","
            << c.getEndDate() << ","
            << c.getContractType() << ","
            << (c.getIsActive() ? 1 : 0) << "\n";
    }
    out.close();
}
