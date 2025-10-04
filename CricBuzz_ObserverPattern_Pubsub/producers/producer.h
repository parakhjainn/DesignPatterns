#pragma once
#include "../models/Match.h"
#include "../subscribers/Subscriber.h"

class Producer {
public:
    virtual ~Producer() = default;

    virtual Match getMatchData() = 0;
    virtual void subscribe(Subscriber* subscriber) = 0;
    virtual void unsubscribe(Subscriber* subscriber) = 0;
    virtual void notifySubscribers() = 0;
};