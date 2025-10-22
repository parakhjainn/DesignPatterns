#pragma once

#include<iostream>
#include "../strategies/SequentialPlayStrategy.hpp"
#include "../strategies/CustomQueueStrategy.hpp"
#include "../strategies/RandomPlayStrategy.hpp"
#include "../enums/PlayStrategyType.hpp"

using namespace std;

class StrategyManager {
    SequentialPlayStrategy* sequentialStrategy;
    RandomPlayStrategy* randomStrategy;
    CustomQueueStrategy* customQueueStrategy;

    StrategyManager() {
        sequentialStrategy = new SequentialPlayStrategy();
        randomStrategy = new RandomPlayStrategy();
        customQueueStrategy = new CustomQueueStrategy();
    }

public:
    static StrategyManager& getInstance() {
        static StrategyManager instance;
        return instance;
    }

    PlayStrategy* getStrategy(PlayStrategyType type) {
        if (type == PlayStrategyType::SEQUENTIAL) {
            return sequentialStrategy;
        } else if (type == PlayStrategyType::RANDOM) {
            return randomStrategy;
        } else {
            return customQueueStrategy;
        }
    }
};
