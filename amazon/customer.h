// 2

#pragma once

#include <iostream>
#include <string>

using namespace std;

class Customer {
    string id;
    string name;
    string email;

public:
    Customer(string name, string email) {
        this -> id = "CUSTOMER random id";
        this -> name = name;
        this -> email = email;
    }

    string getId() {
        return id;
    }

    void setId(string id) {
        this -> id = id;
    }

    string getName() {
        return name;
    }

    void setName(string name) {
        this -> name = name;
    }

    string getEmail() {
        return email;
    }

    void setEmail(string email) {
        this -> email = email;
    } 

};
