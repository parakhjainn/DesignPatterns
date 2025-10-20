// 3

#pragma once

#include <iostream>
#include <string>
#include "product.h"

using namespace std;

class OrderItem {
    string id;
    Product product;
    int productQuantity;

public:
    OrderItem () {}

    OrderItem(Product product, int productQuantity) : product(product), productQuantity (productQuantity) {}

    string getId() {
        return id;
    }

    void setId(string id) {
        this -> id = id;
    }

    Product getProduct() {
        return product;
    }

    int getProductQuantity() {
        return productQuantity;
    }

    void setProductQuantity(int productQuantity) {
        this -> productQuantity = productQuantity;
    }
};
