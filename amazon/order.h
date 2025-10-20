// 4

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "orderItem.h"

using namespace std;

enum class OrderStatus {
    PAYMENT_PENDING, 
    PLACED, 
    SHIPPED, 
    DELIVERED, 
    CANCELLED
};

class Order {
    string id;
    string customerId;
    int orderAmount;
    vector<OrderItem> items;
    OrderStatus orderStatus;

public:
    Order () {}

    Order(string id, string customerId, vector<OrderItem> orderItems) {
        this -> id = id;
        this -> customerId = customerId;
        this -> items = orderItems;
        this -> orderStatus = OrderStatus::PAYMENT_PENDING;
        this -> orderAmount = generateOrderAmount();
    }

    string getId() {
        return id;
    }

    void setId(string id) {
        this -> id = id;
    }

    string getCustomerId() {
        return customerId;
    }

    void setCustomerId(string customerId) {
        this -> customerId = customerId;
    }

    int getOrderAmount() {
        return orderAmount;
    }

    vector<OrderItem> getItems() {
        return items;
    }

    void setItems(vector<OrderItem> items) {
        this -> items = items;
    }

    OrderStatus getOrderStatus() {
        return orderStatus;
    }

    void setOrderStatus(OrderStatus orderStatus) {
        this -> orderStatus = orderStatus;
    }

    int generateOrderAmount() {
        int amount = 0;
        for(OrderItem orderItem: items) {
            amount += orderItem.getProduct().getPrice() * orderItem.getProductQuantity();
        }
        return amount;
    }

};
