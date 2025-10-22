#pragma once

#include "PaymentStrategy.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class CreditCardPaymentStrategy : public PaymentStrategy {
    string cardNumber;

public:
    CreditCardPaymentStrategy(const string& card) {
        cardNumber = card;
    }

    void pay(double amount) override {
        cout << "Paid ₹" << amount << " using Credit Card (" << cardNumber << ")" << endl;
    }
};
