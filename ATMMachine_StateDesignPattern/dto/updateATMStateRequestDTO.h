#pragma once

#include<iostream>
#include<string>
#include "enums/atmState.h"

using namespace std;

class UpdateATMStateRequestDTO {
private:
    string atmId;
    ATMState state;
public:
    UpdateATMStateRequestDTO(string atmId, ATMState state) : atmId(atmId), state(state) {} 

    string getAtmId() const {
        return atmId;
    }

    ATMState getState() const {
        return state;
    }
};

