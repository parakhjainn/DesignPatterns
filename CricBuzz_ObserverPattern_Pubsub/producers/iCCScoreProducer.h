#pragma once
#include <vector>
#include "../models/match.h"
#include "../subscribers/subscriber.h"
#include "producer.h"

using namespace std;

class ICCScoreProducer : public Producer {
private:
    Match match;
    vector<Subscriber*> subscribers;

public:
    ICCScoreProducer(const Match& match) : match(match) {}

    void scoreUpdated() {
        // Call the API layer to get the data
        // and the API layer has the logic for server sent events
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