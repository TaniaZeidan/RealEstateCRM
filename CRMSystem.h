#ifndef CRMSYSTEM_H
#define CRMSYSTEM_H

#include <vector>
#include <string>
#include "Agent.h"
#include "Client.h"
#include "Property.h"
#include "Contract.h"
#include "Inspection.h"

class CRMSystem {
public:
    CRMSystem();
    ~CRMSystem();

    // AGENT CRUD
    void addAgent(const Agent &agent);
    bool removeAgent(int agentId);
    Agent searchAgentById(int agentId) const;
    bool modifyAgent(const Agent &modifiedAgent);
    void displayAgents() const;

    // CLIENT CRUD
    void addClient(const Client &client);
    bool removeClient(int clientId);
    Client searchClientById(int clientId) const;
    bool modifyClient(const Client &modifiedClient);
    void displayClients() const;

    // PROPERTY CRUD
    void addProperty(const Property &property);
    bool removeProperty(int propertyId);
    Property searchPropertyById(int propertyId) const;
    bool modifyProperty(const Property &modifiedProperty);
    void displayProperties() const;

    // CONTRACT CRUD
    void addContract(const Contract &contract);
    bool removeContract(int contractId);
    Contract searchContractById(int contractId) const;
    bool modifyContract(const Contract &modifiedContract);
    void displayContracts() const;

    // Create a contract from existing records
    void createContract(int contractId, int propertyId, int clientId, int agentId,
                        double price, const std::string &startDate,
                        const std::string &endDate, const std::string &contractType, bool isActive);

private:
    std::vector<Agent> agents;
    std::vector<Client> clients;
    std::vector<Property> properties;
    std::vector<Contract> contracts;
    std::vector<Inspection> inspections; // Optional

    // Auto-generated ID counters
    int nextAgentId;
    int nextClientId;
    int nextPropertyId;
    int nextContractId;

    // File persistence functions
    void loadData();
    void saveData();
    void loadAgents();
    void loadClients();
    void loadProperties();
    void loadContracts();

    void saveAgents();
    void saveClients();
    void saveProperties();
    void saveContracts();
};

#endif // CRMSYSTEM_H
