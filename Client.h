#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include "Exceptions.h"

class Client {
public:
    Client();
    Client(int id, const std::string &firstName, const std::string &lastName,
           const std::string &phone, const std::string &email,
           bool isMarried, double budget, const std::string &budgetType);

    // Getters
    int getId() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPhone() const;
    std::string getEmail() const;
    bool getIsMarried() const;
    double getBudget() const;
    std::string getBudgetType() const;

    // Setters
    void setId(int id);
    void setFirstName(const std::string &firstName);
    void setLastName(const std::string &lastName);
    void setPhone(const std::string &phone);
    void setEmail(const std::string &email);
    void setIsMarried(bool isMarried);
    void setBudget(double budget);
    void setBudgetType(const std::string &budgetType); // Must be "rent" or "buy"


    // Validation
    bool isValid() const;

    // Operator overloading
    friend std::ostream& operator<<(std::ostream &os, const Client &client);
    friend std::istream& operator>>(std::istream &is, Client &client);

private:
    int m_id;
    std::string m_firstName;
    std::string m_lastName;
    std::string m_phone;
    std::string m_email;
    bool m_isMarried;
    double m_budget;
    std::string m_budgetType;
};

#endif // CLIENT_H
