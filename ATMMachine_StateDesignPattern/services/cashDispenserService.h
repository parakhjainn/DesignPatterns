#pragma once

#include <iostream>
#include "models/atm.h"

class CashDispenserService {
public:
    virtual void dispenseCash(ATM* atm, int amount) = 0;

    virtual ~CashDispenserService() {}
};