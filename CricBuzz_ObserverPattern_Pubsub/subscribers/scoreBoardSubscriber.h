#pragma once
#include <vector>
#include "../models/match.h"
#include "../models/innings.h"
#include "../producers/producer.h"
#include "subscriber.h"
using namespace std;

class ScoreBoardSubscriber : public Subscriber {
private:
    Match match;
    vector<Producer*> producers;

public:
    ScoreBoardSubscriber(const Match& match, const vector<Producer*>& producers)
        : match(match), producers(producers) {
        for (auto* producer : this->producers) {
            producer->subscribe(this);
        }
    }

    void update(Producer* producer) override {
        bool isFirstInnings = producer->getMatchData().getIsFirstInnings();
        Innings inningsProducer = isFirstInnings ? producer->getMatchData().getInnings1()
                                                 : producer->getMatchData().getInnings2();

        Innings inningsSubscriber = isFirstInnings ? match.getInnings1()
                                                   : match.getInnings2();

        inningsSubscriber.setCurrentScore(inningsProducer.getCurrentScore());
        inningsSubscriber.setCurrentOver(inningsProducer.getCurrentOver());
        inningsSubscriber.setCurrentBall(inningsProducer.getCurrentBall());
        inningsSubscriber.setWickets(inningsProducer.getWickets());

        // If you want to update the match's innings, you may need to set it back:
        if (isFirstInnings) {
            match.setInnings1(inningsSubscriber);
        } else {
            match.setInnings2(inningsSubscriber);
        }
    }
};