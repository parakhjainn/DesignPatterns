#pragma once

#include <iostream>
#include "cashDispenseService.h"
#include "apis/backendAPI.h"
#include "apis/nodeBackendAPI.h"
#include "DTO/getATMAmountRequestDTO.h"
#include "models/atm.h"

using namespace std;

class CashDispenseServiceImpl : public CashDispenserService {
private:
    BackendAPI* backendAPI;
public:

    CashDispenseServiceImpl() {
        this->backendAPI = new NodeBackendAPI();
    }

    void dispenseCash(ATM* atm, int amount) override {
        // call the server to dispense the cash
        int atmAmount = this->backendAPI->getATMAMount(new GetATMAmountRequestDTO(atm->getAtmId()));

        if(atmAmount < amount) {
            throw runtime_error("ATM does not have enough cash to dispense");
        }

        cout << "Dispensing cash: " << amount << endl;
    }

    ~CashDispenseServiceImpl() {
        delete backendAPI;
    }
};