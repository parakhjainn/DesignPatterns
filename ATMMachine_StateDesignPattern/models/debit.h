#pragma once
#include <iostream>

class Debit {
public:
    virtual void makePinPayment() = 0;
    virtual ~Debit() {}
};