#pragma once

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class User {
    string userId; // can be uuid
    string name;
    string email;

public:
    User(string userId, string name, string email)
        : userId(userId), name(name), email(email) {}

    string getId() const {
        return userId; 
    }

    string getName() const { 
        return name; 
    }
    
    string getEmail() const { 
        return email; 
    }

    void setName(string name) {
        this -> name = name;
    }

    void setEmail(string email) {
        this -> email = email;
    }
    
};