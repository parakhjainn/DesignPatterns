#include <iostream>
#include "amazonService.h"
#include "customer.h"
#include "product.h"
#include "cart.h"
#include "payment.h"
#include "upiPayment.h"
#include "creditCardPayment.h"
#include "order.h"

using namespace std;

int main() {
    // Get the singleton instance
    AmazonService& amazon = AmazonService::getInstance();

    // Create customers
    Customer customer1("Yuvraj Singh", "abc@gmail.com");
    Customer customer2("Leo Messi", "xyz@gmail.com");

    // Create products
    Product product1("Iphone 16 phone", 1000, 1, ProductCategory::ELECTRONICS);
    Product product2("Samsung fold phone", 800, 2, ProductCategory::ELECTRONICS);

    // Register customers and products
    amazon.registerCustomer(customer1);
    amazon.registerCustomer(customer2);

    amazon.addProduct(product1);
    amazon.addProduct(product2);

    // Create payments
    UpiPayment payment1;
    CreditCartPayment payment2;

    // Operation 1: Place order for customer 1
    Cart cart1;
    cart1.addItem(product1, 1);  // Assuming Cart stores Product* not copies
    amazon.placeOrder(customer1, cart1, payment1);

    // // Operation 2: Place order for customer 2
    Cart cart2;
    cart2.addItem(product2, 1);
    amazon.placeOrder(customer2, cart2, payment2);

    // Operation 3: Search
    vector<Product> searchResults = amazon.searchProducts("ph");

    cout << "Search Results:\n";
    for (auto& product : searchResults) {
        cout << product.getName() << endl;
    }

    return 0;
}
