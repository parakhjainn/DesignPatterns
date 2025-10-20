// 1

#pragma once

#include <iostream>
#include <string>
#include <mutex>

using namespace std;

enum class ProductCategory {
    CLOTHING, 
    ELECTRONICS, 
    HOUSEHOLD
};

class Product {
    string id;
    string name;
    int price;
    int stock;
    ProductCategory productCategory;

public:
    Product() {}

    Product(string name, int price, int stock, ProductCategory productCategory) {
        this -> id = "PRODUCT random id" + to_string(stock);
        this -> name = name;
        this -> price = price;
        this -> stock = stock;
        this -> productCategory = productCategory;
    }

    string getId() {
        return id;
    }
    
    string getName() {
        return name;
    }

    int getPrice() {
        return price;
    }

    int getStock() {
        return stock;
    }

    // Current approach: synchronized methods
    // Pros: Simple, thread-safe for single JVM, prevents race conditions on stock.
    // Cons: Can be a bottleneck under high concurrency, not scalable for distributed systems.

    bool isAvailable(int quantity) {
        return stock >= quantity;
    }

    void updateStock(int delta) {
        this -> stock += delta;
    }


    // Future approach: AtomicInteger for stock management
    // Pros: Non-blocking, allows concurrent updates, better performance under high load.
    // Cons: Requires careful handling of atomic operations, may not prevent all

};