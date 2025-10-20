#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <random>
#include <sstream>

#include "customer.h"
#include "product.h"
#include "order.h"
#include "cart.h"
#include "payment.h"

using namespace std;

class AmazonService {
    unordered_map<string, Customer> customers;
    unordered_map<string, Product> products;
    unordered_map<string, Order> orders;

    AmazonService() = default;

public:
    static AmazonService& getInstance() {
        static AmazonService instance;
        return instance;
    }

    void registerCustomer(Customer& customer) {
        customers.emplace(customer.getId(), customer);
    }

    void addProduct(Product& product) {
        products.emplace(product.getId(), product);
    }

    Customer* getCustomer(string& id) {
        auto it = customers.find(id);
        return it != customers.end() ? &it->second : nullptr;
    }

    Product* getProduct(string& id) {
        auto it = products.find(id);
        return it != products.end() ? &it->second : nullptr;
    }

    Order* placeOrder(Customer& customer, Cart& cart, Payment& payment) {
        vector<OrderItem> inStockItems;

        for (auto& item : cart.getItems()) {
            Product product = item.getProduct();  // This is by value
            int quantity = item.getProductQuantity();

            if (product.isAvailable(quantity)) {
                product.updateStock(-quantity);
                inStockItems.push_back(item);
            }
        }

        if (inStockItems.empty()) {
            throw runtime_error("No available products in cart.");
        }

        string orderId = "ORDER random id";
        Order order(orderId, customer.getId(), inStockItems);
        order.setOrderStatus(OrderStatus::PAYMENT_PENDING);
        cart.emptyCart();

        if (payment.processPayment(order.getOrderAmount())) {
            order.setOrderStatus(OrderStatus::PLACED);
        } else {
            order.setOrderStatus(OrderStatus::CANCELLED);
            for (auto& oi : order.getItems()) {
                Product p = oi.getProduct();  // Legal, binds to temporary
                p.updateStock(oi.getProductQuantity());
            }
        }

        // Save and return pointer to order
        orders[orderId] = order;
        return &orders[orderId];
    }

    Order* getOrder(string& orderId) {
        auto it = orders.find(orderId);
        return it != orders.end() ? &it->second : nullptr;
    }

    vector<Product> searchProducts(string keyword) {
        vector<Product> result;
        string key = keyword;
        transform(key.begin(), key.end(), key.begin(), ::tolower);

        for (auto& pair : products) {
            Product& product = pair.second;
            string name = product.getName();         // Original name
            string loweredName = name;               // Copy for safe transformation
            transform(loweredName.begin(), loweredName.end(), loweredName.begin(), ::tolower);
            
            if (loweredName.find(key) != string::npos) {
                result.push_back(product);  // copy
            }
        }
        return result;
    }

};
