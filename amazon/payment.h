// 6
#pragma once 

#include<iostream>

class Payment {
public:
    virtual bool processPayment(int amount) = 0;
    virtual ~Payment() = default;
};
