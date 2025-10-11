#pragma once

#include <iostream>

using namespace std;

class StripePaymentProcessor {
public:

    void makeStripePayment() {
        // stripe implementation
        cout << "Making payment using stripe" << endl;
    }

    void getStripePayment(long id) {
        // stripe implementation
        cout << "Getting payment status for stripe" << endl;
    }
};