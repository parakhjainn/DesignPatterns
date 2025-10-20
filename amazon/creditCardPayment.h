// 8

#pragma once

#include <iostream>
#include "payment.h"

using namespace std;

class CreditCartPayment : public Payment {
public: 
    bool processPayment(int amount) override {
        cout << "Payment via Credit Card \n";
        return true;
    }

};