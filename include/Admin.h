#ifndef ADMIN_H
#define ADMIN_H

#include <string>

class Admin {
    std::string username;
    std::string password;

public:
    Admin();
    Admin(const std::string& username, const std::string& password);
    bool authenticate(const std::string& user, const std::string& pwd) const;
    std::string getUsername() const;
};

#endif

