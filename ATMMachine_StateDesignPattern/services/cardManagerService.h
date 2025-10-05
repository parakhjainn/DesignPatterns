#pragma once

#include <iostream>
#include <string>
#include "models/card.h"

using namespace std;

class CardManagerService {
public:
    virtual bool validateCard(Card card, string pin) = 0;

    virtual bool validateWithdrawl(int transactionId, double amount) = 0;

    virtual bool doTransaction(Card card, double amount, int transactionId) = 0;

    virtual ~CardManagerService() {}
};