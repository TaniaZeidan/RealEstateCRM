#include "Client.h"
#include "Exceptions.h"
#include <stdexcept>

Client::Client() : m_id(-1), m_isMarried(false), m_budget(0.0), m_budgetType("buy") {}

Client::Client(int id, const std::string &firstName, const std::string &lastName,
               const std::string &phone, const std::string &email,
               bool isMarried, double budget, const std::string &budgetType)
    : m_id(id), m_firstName(firstName), m_lastName(lastName),
      m_phone(phone), m_email(email), m_isMarried(isMarried), m_budget(budget), m_budgetType(budgetType)
{}

int Client::getId() const { return m_id; }
std::string Client::getFirstName() const { return m_firstName; }
std::string Client::getLastName() const { return m_lastName; }
std::string Client::getPhone() const { return m_phone; }
std::string Client::getEmail() const { return m_email; }
bool Client::getIsMarried() const { return m_isMarried; }
double Client::getBudget() const { return m_budget; }
std::string Client::getBudgetType() const { return m_budgetType; }

void Client::setId(int id) { m_id = id; }
void Client::setFirstName(const std::string &firstName) { m_firstName = firstName; }
void Client::setLastName(const std::string &lastName) { m_lastName = lastName; }
void Client::setPhone(const std::string &phone) { m_phone = phone; }
void Client::setEmail(const std::string &email) { m_email = email; }
void Client::setIsMarried(bool isMarried) { m_isMarried = isMarried; }
void Client::setBudget(double budget) { m_budget = budget; }
void Client::setBudgetType(const std::string &budgetType) {
    if(budgetType != "rent" && budgetType != "buy") {
        throw ValidationException("Budget type must be 'rent' or 'buy'.");
    }
    m_budgetType = budgetType;
}

bool Client::isValid() const {
    if(m_firstName.empty() || m_lastName.empty()) 
        return false;
    if(m_budget < 0) 
        return false;
    if(!m_email.empty() && m_email.find('@') == std::string::npos) 
        return false;
    if(m_budgetType != "rent" && m_budgetType != "buy") 
        return false;
    return true;
}

std::ostream& operator<<(std::ostream &os, const Client &client) {
    os << "ID: " << client.m_id 
       << "\nName: " << client.m_firstName << " " << client.m_lastName
       << "\nPhone: " << client.m_phone
       << "\nEmail: " << client.m_email
       << "\nMarried: " << (client.m_isMarried ? "Yes" : "No")
       << "\nBudget: " << client.m_budget
       << "\nBudget Type: " << client.m_budgetType;
    return os;
}

std::istream& operator>>(std::istream &is, Client &client) {
    is >> client.m_id >> client.m_firstName >> client.m_lastName >> client.m_phone
       >> client.m_email >> client.m_isMarried >> client.m_budget >> client.m_budgetType;
    return is;
}
