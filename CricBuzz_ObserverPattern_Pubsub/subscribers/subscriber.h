#pragma once
#include <iostream>
#include "../producers/producer.h"

class Subscriber {
public:
    virtual ~Subscriber() = default; // Virtual destructor for interface safety

    // Pure virtual function equivalent to Java's interface method
    virtual void update(Producer* producer) = 0;
};