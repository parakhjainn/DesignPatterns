#pragma once

#include<iostream>
#include<string>
using namespace std;

class CreateTransactionRequestDTO {
private:
    string atmId;
public:
    CreateTransactionRequestDTO(string atmId) : atmId(atmId) {} 

    string getAtmId() const {
        return atmId;
    }
};