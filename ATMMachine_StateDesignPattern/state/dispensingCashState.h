#pragma once

#include <iostream>
#include "state.h"
#include "../enums/atmState.h"
#include "../models/atm.h"
#include "../models/card.h"
#include "../services/cashDispenserService.h"
#include "../services/cashDispenserServiceImpl.h"   
#include "../factories/cardManagerFactory.h"
#include "../services/cardManagerService.h"

using namespace std;

class DispensingCashState : public State {
private:
    ATM* atm;

    CashDispenserService* cashDispenserService;

public:
    DispensingCashState(ATM* atm) {
        this->atm = atm;
        this->cashDispenserService = new CashDispenserServiceImpl();
    }

    int initTransaction() {
        throw invalid_argument("Cannot init transaction while dispensing cash");
    }

    bool readCardDetailsAndPin(Card* card, string pin) {
        throw invalid_argument("Cannot read card details and pin while dispensing cash");
    }

    int dispenseCash(Card* card, int amount, int transactionId) {
        CardManagerService* manager = CardManagerFactory::getCardManager(card->getCardType());

        bool isTxnSuccessful = manager->doTransaction(card, amount, transactionId);
        
        if(isTxnSuccessful) {
            this->cashDispenserService->dispenseCash(this->atm, amount);
        } else {
            cout << "Something went wrong" << endl;
        }
        this->atm->changeState(new EjectingCardState(this->atm));

        return amount;
    }

    void ejectCard() {
        throw invalid_argument("Cannot eject card while dispensing cash");
    }

    bool readCashWithdrawDetails(Card* card, int transactionId, int amount) {
        throw invalid_argument("Cannot read cash withdraw details while dispensing cash");
    }

    bool cancelTransaction(int transactionId) {
        throw invalid_argument("Cannot cancel transaction while dispensing cash");
    }

    ATMState getState() {
        return ATMState::DISPENSING_CASH;
    }

};
