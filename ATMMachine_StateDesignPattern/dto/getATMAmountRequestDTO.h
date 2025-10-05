#pragma once

#include<iostream>
#include<string>
using namespace std;

class GetATMAmountRequestDTO {
private:
    string atmId;
public:
    GetATMAmountRequestDTO(string atmId) : atmId(atmId) {} 

    string getAtmId() const {
        return atmId;
    }
};
