#ifndef EMPLOYEEACCOUNT_H
#define EMPLOYEEACCOUNT_H

#include "UserAccount.h"

class EmployeeAccount : public UserAccount {
public:
    EmployeeAccount(const std::string &username, const std::string &password) : UserAccount(username, password) {}
    virtual std::string getRole() const override { return "Employee"; }
};

#endif // EMPLOYEEACCOUNT_H
