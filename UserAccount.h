#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include <string>
using std::string;

class UserAccount {
public:
    UserAccount(const string &username, const string &password) : username(username), password(password) {}
    virtual ~UserAccount() {}
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    virtual string getRole() const = 0;  // pure virtual function

protected:
    string username;
    string password;
};

#endif // USERACCOUNT_H
