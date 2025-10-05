#pragma once

#include <iostream>
#include "enums/cardType.h"
#include "services/cardManagerService.h"
#include "services/debitCardManagerService.h"
#include "services/creditCardManagerService.h"
using namespace std;

class CardManagerFactory {
    public:
        static CardManagerService* getCardManager(CardType cardType) {
            CardManagerService* cardManagerService = nullptr;
            if(cardType == CardType::DEBIT) {
                cardManagerService = new DebitCardManagerService();
            } else if(cardType == CardType::CREDIT) {
                cardManagerService = new CreditCardManagerService();
            } else {
                throw invalid_argument("Invalid Card Type");
            }

            return cardManagerService;
        }
};
