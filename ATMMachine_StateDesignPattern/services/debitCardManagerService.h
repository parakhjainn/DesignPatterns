#pragma once

#include <iostream>
#include <string>
#include "models/card.h"
#include "cardManagerService.h"
using namespace std;

class DebitCardManagerService : public CardManagerService {
public:
    bool validateCard(Card card, string pin) override {
        // ideally we should make these also connect to API
        return true;
    }   

    bool validateWithdrawl(int transactionId, double amount) override {
        // ideally we should make these also connect to API
        return true;
    }

    bool doTransaction(Card card, double amount, int transactionId) override {
        // ideally we should make these also connect to API
        return true;
    }
};
