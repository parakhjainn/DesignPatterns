#pragma once

#include <iostream>

using namespace std;

class RazorpayPaymentProcessor {
public:

    void makeRazorPayment() {
        // stripe implementation
        cout << "Making payment using razorpay" << endl;
    }

    void getRazorPayStatus(long id) {
        // stripe implementation
        cout << "Getting payment status for razorpay" << endl;
    }
};