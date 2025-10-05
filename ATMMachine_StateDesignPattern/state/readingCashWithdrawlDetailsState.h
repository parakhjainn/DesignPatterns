#pragma once

#include <iostream>
#include "state.h"
#include "models/atm.h"
#include "models/card.h"
#include "enums/atmState.h"
#include "factories/cardManagerFactory.h"
#include "services/cardManagerService.h"

using namespace std;

class ReadingCashWithdrawlDetailsState : public State {
private:
    ATM* atm;
public:
    ReadingCashWithdrawlDetailsState(ATM* atm) : atm(atm) {}

    int initTransaction() override {
        throw runtime_error("Cannot init transaction while reading cash withdraw details");
    }

    bool readCardDetailsAndPin(Card card, string pin) override {
        throw runtime_error("Cannot read card details and pin without inserting card");
    }

    int dispenseCash(Card card, int amount, int transactionId) override {
        throw runtime_error("Cannot dispense cash without reading card details and pin");
    }

    void ejectCard() override {
        throw runtime_error("Cannot eject card without reading card details and pin");
    }

    bool readCashWithdrawDetails(Card card, int transactionId, int amount) override {
        // CardManagerFactory to get appropriate card manager based on card type like Credit/Debit 
        // and avoid Open/Closed principle violation here
        CardManagerService* manager = CardManagerFactory::getCardManager(card.getCardType());
        bool isWithdrawlValid = manager->validateWithdrawl(transactionId, amount);
        if (isWithdrawlValid) {
            this->atm->changeState(new DispensingCashState(this->atm));
        } else {
            this->atm->changeState(new EjectingCardState(this->atm));
        }
        delete manager;
        return isWithdrawlValid;
    }

    bool cancelTransaction(int transactionId) override {
        try {
            this->atm->changeState(new ReadyForTransactionState(this->atm));
            return true;
        } catch (exception& e) {
            throw runtime_error("Cannot cancel transaction while reading cash withdraw details");
        }
    }

    ATMState getState() override {
        return ATMState::READING_CASH_WITHDRAW_DETAILS;
    }
};