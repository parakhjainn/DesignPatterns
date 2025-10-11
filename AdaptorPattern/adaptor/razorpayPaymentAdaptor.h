#pragma once

#include <iostream>
#include "../adaptee/razorpayPaymentProcessor.h"
#include "../target/paymentGateway.h"

using namespace std;

class RazorPayPaymentAdapter : public PaymentGateway {
private:
    RazorpayPaymentProcessor* razorpayPaymentProcessor;
public:
    RazorPayPaymentAdapter(RazorpayPaymentProcessor* processor) : razorpayPaymentProcessor(processor) {}

    void makePayment() override {
        razorpayPaymentProcessor->makeRazorPayment();
    }

    void getStatus(long id) override {
        razorpayPaymentProcessor->getRazorPayStatus(id);
    }

    ~RazorPayPaymentAdapter() {
        delete razorpayPaymentProcessor;
    }
};