#pragma once

#include "Order.h"

using namespace std;

class PickupOrder : public Order {
    string restaurantAddress;

public:
    PickupOrder() {
        restaurantAddress = "";
    }

    string getType() const override {
        return "Pickup";
    }

    //Getter and Setters
    void setRestaurantAddress(const string& addr) {
        restaurantAddress = addr;
    }

    string getRestaurantAddress() const {
        return restaurantAddress;
    }
};
