// 6

#pragma once

#include<iostream>

using namespace std;

class User {
    int id;
    string email;
    string phone;

public:
    User(int id_, string email_, string phone_) : id(id_), email(email_), phone(phone_) {}

    int getId() {
        return id;
    }

    string getEmail() {
        return email;
    }

    string getPhone() {
        return phone;
    }

    virtual ~User() = default;
};