#ifndef ADMINACCOUNT_H
#define ADMINACCOUNT_H

#include "UserAccount.h"

class AdminAccount : public UserAccount {
public:
    AdminAccount(const std::string &username, const std::string &password) : UserAccount(username, password) {}
    virtual std::string getRole() const override { return "Admin"; }
};

#endif // ADMINACCOUNT_H
