#pragma once

#include <iostream>
#include <string>
#include "state.h"
#include "models/atm.h"
#include "models/card.h"
#include "enums/atmState.h"
#include "enums/cardType.h"
#include "factories/cardManagerFactory.h"
#include "services/cardManagerService.h"

using namespace std;

class ReadCardDetailsAndPinState : public State {
private:
    ATM* atm;

public:
    ReadCardDetailsAndPinState(ATM* atm) : atm(atm) {}   

    int initTransaction() override {
        throw runtime_error("Cannot init transaction while reading card details and pin");
    }

    bool readCardDetailsAndPin(Card card, string pin) override {
        // CardManagerFactory to get appropriate card manager based on card type like Credit/Debit 
        // and avoid Open/Closed principle violation here
        CardManagerService* manager = CardManagerFactory::getCardManager(card.getCardType());
        bool isCardValid = manager->validateCard(card, pin);
        if (isCardValid) {
            this->atm->changeState(new ReadingCashWithdrawlDetailsState(this->atm));
        } else {
            this->atm->changeState(new EjectingCardState(this->atm));
        }
        delete manager;
        return isCardValid;
    }

    int dispenseCash(Card card, int amount, int transactionId) override {
        throw runtime_error("Cannot dispense cash while reading card details and pin");
    }

    void ejectCard() override {
        throw runtime_error("Cannot eject card while reading card details and pin");
    }

    bool readCashWithdrawDetails(Card card, int transactionId, int amount) override {
        throw runtime_error("Cannot read cash withdraw details while reading card details and pin");
    }

    bool cancelTransaction(int transactionId) override {
        try {
            this->atm->changeState(new ReadyForTransactionState(this->atm));
            return true;
        } catch (exception& e) {
            throw runtime_error("Cannot cancel transaction while reading card details and pin");
        }
    }

    ATMState getState() override {
        return ATMState::READ_CARD_DETAILS_AND_PIN;
    }
    
};