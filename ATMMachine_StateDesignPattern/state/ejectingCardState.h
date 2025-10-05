#pragma once

#include <iostream>
#include "state.h"
#include "../enums/atmState.h"
#include "../models/atm.h"
#include "../models/card.h"

using namespace std;

class EjectingCardState : public State {
private:
    ATM* atm;

public:
    EjectingCardState(ATM* atm) {
        this->atm = atm;
    }

    int initTransaction() {
        throw invalid_argument("Cannot init transaction while ejecting card");
    }

    bool readCardDetailsAndPin(Card* card, string pin) {
        throw invalid_argument("Cannot read card details and pin while ejecting card");
    }

    int dispenseCash(Card* card, int amount, int transactionId) {
        throw invalid_argument("Cannot dispense cash while ejecting card");
    }

    void ejectCard() {
        cout << "Card ejected, please take it" << endl;
        this->atm->changeState(new ReadyForTransactionState(this->atm));
    }

    bool readCashWithdrawDetails(Card* card, int transactionId, int amount) {
        throw invalid_argument("Cannot read cash withdraw details while ejecting card");
    }

    bool cancelTransaction(int transactionId) {
        throw invalid_argument("Cannot cancel transaction while ejecting card");
    }

    ATMState getState() {
        return ATMState::EJECTING_CARD;
    }

};
