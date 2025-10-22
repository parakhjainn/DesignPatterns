#pragma once

#include <vector>
#include <iostream>
#include "../models/Order.h"

using namespace std;

class OrderManager {
private:
    vector<Order*> orders;

    OrderManager() {} // Private Constructor

public:
    static OrderManager& getInstance() {
        static OrderManager instance;
        return instance;
    }

    void addOrder(Order* order) {
        orders.push_back(order);
    }

    void listOrders() {
        cout << "\n--- All Orders ---" << endl;
        for (auto order : orders) {
            cout << order->getType() << " order for " << order->getUser()->getName()
                    << " | Total: ₹" << order->getTotal()
                    << " | At: " << order->getScheduled() << endl;
        }
    }
};
