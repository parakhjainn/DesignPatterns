#pragma once

#include <iostream>
#include "enums/cardType.h"
#include "visa.h"
#include "debit.h"
#include "card.h"

using namespace std;

class VisaDebitCard : public Card, public Debit, public Visa {
public:
    VisaDebitCard(long cardNumber, int pin, string name, CardType cardType, string bankName)
        : Card(cardNumber, pin, name, cardType, bankName) {}    

    void makePinPayment() override {
        this->connectToVisa();  
        cout << "Making payment with pin" << endl;
    }

    void connectToVisa() override {
        cout << "Connecting to Visa" << endl;
    }
};

