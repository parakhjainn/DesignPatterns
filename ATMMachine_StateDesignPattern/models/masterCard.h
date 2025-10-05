#pragma once
#include <iostream>

class MasterCard {
public:
    virtual void connectToMasterCard() = 0;
    virtual ~MasterCard() {}
};