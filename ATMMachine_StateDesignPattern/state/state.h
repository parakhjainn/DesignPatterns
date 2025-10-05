#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "enums/atmState.h"
#include "models/card.h"

using namespace std;

class State {
public:
    virtual int initTransaction() = 0;

    // returns true if card is valid and false otherwise
    virtual bool readCardDetailsAndPin(Card* card, const string &pin) = 0; 

    // returns the amount dispensed
    virtual int dispenseCash(Card* card, int amount, int transactionId) = 0;

    virtual void ejectCard() = 0;

    // returns true if cash withdrawl details are valid and false otherwise
    virtual bool readCashWithdrawDetails(Card* card, int transactionId, int amount) = 0; 

    // returns true if transaction is cancelled and false otherwise
    virtual bool cancelTransaction(int transactionId) = 0; 
    
    virtual ATMState getState() = 0;
    
    virtual ~State() = default;
};
