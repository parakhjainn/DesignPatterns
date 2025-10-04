#pragma once
#include <vector>
#include <string>
#include "../producers/Producer.h"
#include "Subscriber.h"
using namespace std;

class CommentarySubscriber : public Subscriber {
private:
    vector<string> commentaries;
    vector<Producer*> producers;

public:
    CommentarySubscriber(const vector<Producer*>& producers)
        : producers(producers) {
        for (auto* producer : this->producers) {
            producer->subscribe(this);
        }
    }

    void update(Producer* producer) override {
        const auto& commentary = producer->getMatchData().getCommentary();
        if (!commentary.empty()) {
            commentaries.push_back(commentary.back());
        }
    }
};