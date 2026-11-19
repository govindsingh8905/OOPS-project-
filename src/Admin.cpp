#include "Admin.h"

using namespace std;

Admin::Admin() : username("admin"), password("admin123") {}

Admin::Admin(const string& username, const string& password)
    : username(username), password(password) {}

bool Admin::authenticate(const string& user, const string& pwd) const {
    return username == user && password == pwd;
}

string Admin::getUsername() const {
    return username;
}

