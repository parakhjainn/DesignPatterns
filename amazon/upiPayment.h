// 7

#pragma once

#include <iostream>
#include "payment.h"

using namespace std;

class UpiPayment : public Payment {
public: 
    bool processPayment(int amount) override {
        cout << "Payment via UPI \n";
        return true;
    }

};