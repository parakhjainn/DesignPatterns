#pragma once
#include <iostream>

class Credit {
public:
    virtual void makePinPayment() = 0;
    virtual ~Credit() {}
};