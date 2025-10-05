#pragma once
#include <iostream>

class Visa {
public:
    virtual void connectToVisa() = 0;
    virtual ~Visa() {}
};