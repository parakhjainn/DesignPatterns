#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include "../models/Restaurant.h"

using namespace std;

class RestaurantManager {
    vector<Restaurant*> restaurants;

    RestaurantManager() {}  // private constructor

public:
    static RestaurantManager& getInstance() {
        static RestaurantManager instance;
        return instance;
    }

    void addRestaurant(Restaurant* r) {
        restaurants.push_back(r);
    }

    vector<Restaurant*> searchByLocation(string loc) {
        vector<Restaurant*> result;
        transform(loc.begin(), loc.end(), loc.begin(), ::tolower);
        for (auto r : restaurants) {
            string rl = r->getLocation();
            transform(rl.begin(), rl.end(), rl.begin(), ::tolower);
            if (rl == loc) {
                result.push_back(r);
            }
        }
        return result;
    }
};

