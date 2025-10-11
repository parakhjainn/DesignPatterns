#pragma once

class PaymentGateway {
public:
    virtual void makePayment() = 0;
    virtual void getStatus(long id) = 0;
    virtual ~PaymentGateway() {}
};