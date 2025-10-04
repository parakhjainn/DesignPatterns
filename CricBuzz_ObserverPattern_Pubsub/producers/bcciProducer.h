#pragma once
#include <vector>
#include <algorithm>
#include "../models/match.h"
#include "../subscribers/subscriber.h"
#include "producer.h"
using namespace std;

class BcciProducer : public Producer {
private:
    Match match;
    vector<Subscriber*> subscribers;

public:
    BcciProducer(const Match& match) : match(match) {}

    void scoreUpdated(const string& runs, const string& over, const string& ball, const string& wickets, bool isFirstInnings) {
        // Some API or mechanism to fetch data
        this->notifySubscribers();
    }

    Match getMatchData() override {
        return match;
    }

    void subscribe(Subscriber* subscriber) override {
        subscribers.push_back(subscriber);
    }

    void unsubscribe(Subscriber* subscriber) override {
        subscribers.erase(
            remove(subscribers.begin(), subscribers.end(), subscriber),
            subscribers.end()
        );
    }

    void notifySubscribers() override {
        for (auto* sub : subscribers) {
            sub->update(this);
        }
    }
};