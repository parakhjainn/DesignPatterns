#include<iostream>
#include "../adaptee/razorpayPaymentProcessor.h"
#include "../adaptee/stripePaymentProcessor.h"
#include "../adapter/razorpayPaymentAdaptor.h"
#include "../adapter/stripePaymentAdaptor.h"

using namespace std;

int main() {
    // Using Razorpay through the adapter
    RazorpayPaymentProcessor* razorpayPaymentProcessor = new RazorpayPaymentProcessor();
    RazorPayPaymentAdapter* rAdapter = new RazorPayPaymentAdapter(razorpayPaymentProcessor);
    rAdapter->makePayment();
    rAdapter->getStatus(12);

    // Using Stripe through the adapter
    StripePaymentProcessor* stripePaymentProcessor = new StripePaymentProcessor();
    StripePaymentAdapter* sAdapter = new StripePaymentAdapter(stripePaymentProcessor);
    sAdapter->makePayment();
    sAdapter->getStatus(15);

    return 0;
}