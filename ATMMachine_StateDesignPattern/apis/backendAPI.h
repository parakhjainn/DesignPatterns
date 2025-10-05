#pragma once

#include <iostream>
#include <string>
#include "dto/createTransactionRequestDTO.h"
#include "dto/updateATMStateRequestDTO.h"
#include "dto/getATMAmountRequestDTO.h"

using namespace std;    

class BackendAPI {
public:
    virtual int createTransaction(CreateTransactionRequestDTO* createTransactionDTO) = 0;    

    virtual bool updateState(UpdateATMStateRequestDTO* updateATMStateDTO) = 0;

    virtual int getATMAMount(GetATMAmountRequestDTO* getATMAmountRequestDTO) = 0;

    virtual ~BackendAPI() = default; // Virtual destructor for proper cleanup of derived classes
};