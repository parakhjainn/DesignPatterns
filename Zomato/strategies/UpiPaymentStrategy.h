#pragma once

#include "PaymentStrategy.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class UpiPaymentStrategy : public PaymentStrategy {
    string mobile;
    
public:
    UpiPaymentStrategy(const string& mob) {
        mobile = mob;
    }

    void pay(double amount) override {
        cout << "Paid ₹" << amount << " using UPI (" << mobile << ")" << endl;
    }
};
