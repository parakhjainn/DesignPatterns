#pragma once

#include <iostream>
#include "../adaptee/stripePaymentProcessor.h"
#include "../target/paymentGateway.h"

using namespace std;

class StripePaymentAdapter : public PaymentGateway {
private:
    StripePaymentProcessor* stripePaymentProcessor;
public:
    StripePaymentAdapter(StripePaymentProcessor* processor) : stripePaymentProcessor(processor) {}
    
    void makePayment() override {
        stripePaymentProcessor->makeStripePayment();
    }

    void getStatus(long id) override {
        stripePaymentProcessor->getStripePayment(id);
    }

    ~StripePaymentAdapter() {
        delete stripePaymentProcessor;
    }
};
