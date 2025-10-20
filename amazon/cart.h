// 5

#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>
#include "orderItem.h"

using namespace std;

class Cart {
    unordered_map<string, OrderItem> items;

public:
    void addItem(Product& product, int quantity) {
        string prodId = product.getId();

        auto it = items.find(prodId);
        if (it != items.end()) {
            quantity += it->second.getProductQuantity();
        }

        items[prodId] = OrderItem(product, quantity);
    }

    void removeItem(string& productId) {
        items.erase(productId);
    }

    vector<OrderItem> getItems() {
        vector<OrderItem> itemList;
        for (auto& pair : items) {
            itemList.push_back(pair.second);
        }
        return itemList;
    }

    void emptyCart() {
        items.clear();
    }
};