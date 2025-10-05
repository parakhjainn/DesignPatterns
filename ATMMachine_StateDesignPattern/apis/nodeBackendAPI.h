#pragma once
#include <iostream>
#include <string>
#include "dto/createTransactionRequestDTO.h"
#include "dto/updateATMStateRequestDTO.h"
#include "dto/getATMAmountRequestDTO.h"

using namespace std;

class NodeBackendAPI : public BackendAPI {
public: 

    int createTransaction(CreateTransactionRequestDTO* createTransactionDTO) override {
        // 1. Validations
        // if (createTransactionDTO->getAtmId().empty()) {
        //     throw invalid_argument("ATM ID cannot be empty");
        // }

        // 2. Connect to the backend
        // To mimic the backend call let's return a new random transaction ID

        // 3. Return the response
        return rand() % 1000; // Random transaction ID between 0 and 999
    }   

    bool updateState(UpdateATMStateRequestDTO* updateATMStateDTO) override {
        // Assume that there is the implementation that calls the backend to update the state of the ATM

        return true; // mimicked response
    }   

    int getATMAMount(GetATMAmountRequestDTO* getATMAmountRequestDTO) override {
        return 10000; // Mimicked amount
    }   

    ~NodeBackendAPI() override = default; // Default destructor
};