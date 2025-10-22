/*

Requirements
    The vending machine should support multiple products with different prices and quantities.
    The machine should accept coins of different denominations.
    The machine should dispense the selected product and return change if necessary.
    The machine should keep track of the available products and their quantities.
    The machine should provide an interface for restocking products and collecting money.
    The machine should handle exceptional scenarios, such as insufficient funds or out-of-stock products.

    The machine should handle multiple transactions concurrently and ensure data consistency.

*/


#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---- Product definition ----
struct Product {
    string name;
    int price;
    int quantity;
    Product(string n, int p, int q) : name(n), price(p), quantity(q) {}
};

// Forward declaration
class VendingMachine;
class VendingState;


// Abstract State Interface
class VendingState {
public:
    virtual VendingState* insertCoin(VendingMachine* machine, int coin) = 0;
    virtual VendingState* selectItem(VendingMachine* machine, int productIdx) = 0;
    virtual VendingState* dispense(VendingMachine* machine) = 0;
    virtual VendingState* returnCoin(VendingMachine* machine) = 0;
    virtual VendingState* refill(VendingMachine* machine, int productIdx, int quantity) = 0;
    virtual string getStateName() = 0;
};

// Context Class - Vending Machine
class VendingMachine {
private:
    VendingState* currentState;
    vector<Product> products;
    int selectedProductIdx;
    int insertedCoins;

    // State objects (we'll initialize these)
    VendingState* noCoinState;
    VendingState* hasCoinState;
    VendingState* dispenseState;
    VendingState* soldOutState;

public:
    VendingMachine(vector<Product> prods);

    // Delegate to current state and update state based on return value
    void insertCoin(int coin);
    void selectItem(int productIdx);
    void dispense();
    void returnCoin();
    void refill(int productIdx, int quantity);

    // Print the status of Vending Machine
    void printStatus();

    // Getters for states
    VendingState* getNoCoinState() { 
        return noCoinState;
    }
    VendingState* getHasCoinState() { 
        return hasCoinState;
    }
    VendingState* getDispenseState() { 
        return dispenseState; 
    }
    VendingState* getSoldOutState() { 
        return soldOutState;
    }

    // Data access methods
    int getInsertedCoin() { 
        return insertedCoins; 
    }
    void setInsertedCoin(int coin) { 
        insertedCoins = coin; 
    }
    void addCoin(int coin) { 
        insertedCoins += coin; 
    }
    vector<Product>& getProducts() { 
        return products; 
    }
    Product& getSelectedProduct() { 
        return products[selectedProductIdx]; 
    }
    int getSelectedProductIdx() { 
        return selectedProductIdx; 
    }
    void setSelectedProductIdx(int idx) { 
        selectedProductIdx = idx; 
    }
    void decrementSelectedProduct() { 
        products[selectedProductIdx].quantity--; 
    }
    void incrementProductQuantity(int idx, int count=1) { 
        products[idx].quantity += count; 
    }
    bool allSoldOut();
};

// Concrete State: No Coin Inserted
class NoCoinState : public VendingState {
public:
    VendingState* insertCoin(VendingMachine* machine, int coin) override {
        machine->setInsertedCoin(coin); // Rs 10
        cout << "Coin inserted. Current balance: Rs " << coin << endl;
        return machine->getHasCoinState(); // Transition to HasCoinState
    }

    VendingState* selectItem(VendingMachine* machine, int productIdx) override {
        cout << "Please insert coin first!" << endl;
        return machine->getNoCoinState(); // Stay in same state
    }

    VendingState* dispense(VendingMachine* machine) override {
        cout << "Please insert coin and select item first!" << endl;
        return machine->getNoCoinState(); // Stay in same state
    }
    
    VendingState* returnCoin(VendingMachine* machine) override {
        cout << "No coin to return!" << endl;
        return machine->getNoCoinState(); // Stay in same state
    }

    VendingState* refill(VendingMachine* machine, int productIdx, int quantity) override {
        cout << "Refilling product " << machine->getProducts()[productIdx].name << endl;
        machine->incrementProductQuantity(productIdx, quantity);
        return machine->getNoCoinState(); // Stay in same state
    }
    
    string getStateName() override { 
        return "NO_COIN"; 
    }
};

// Concrete State: Coin Inserted
class HasCoinState : public VendingState {
public:
    VendingState* insertCoin(VendingMachine* machine, int coin) override {
        machine->addCoin(coin);
        cout << "Additional coin inserted. Current balance: Rs " << machine->getInsertedCoin() << endl;
        return machine->getHasCoinState(); // Stay in same state
    }

    VendingState* selectItem(VendingMachine* machine, int productIdx) override {
        if (productIdx < 0 || productIdx >= machine->getProducts().size()) {
            cout << "Invalid product!" << endl;
            return machine->getHasCoinState();
        }
        machine->setSelectedProductIdx(productIdx);
        Product& prod = machine->getSelectedProduct();
        if (prod.quantity == 0) {
            cout << "Selected item '" << prod.name << "' is sold out." << endl;
            return machine->getHasCoinState();
        }
        if (machine->getInsertedCoin() >= prod.price) {
            int change = machine->getInsertedCoin() - prod.price;
            cout << "Item '" << prod.name << "' selected. Dispensing..." << endl;
            if (change > 0) cout << "Change returned: Rs " << change << endl;
            machine->setInsertedCoin(0);
            
            return machine->getDispenseState(); // Transition to DispenseState
        } 
        else {
            int needed = prod.price - machine->getInsertedCoin();
            cout << "Insufficient funds for '" << prod.name << "'. Need Rs " << needed << " more." << endl;
            return machine->getHasCoinState();
        }
    }
    
    VendingState* dispense(VendingMachine* machine) override {
       cout << "Please select an item first!" <<endl;
        return machine->getHasCoinState(); // Stay in same state
    }
    
    VendingState* returnCoin(VendingMachine* machine) override {
       cout << "Coin returned: Rs " << machine->getInsertedCoin() <<endl;
        machine->setInsertedCoin(0);
        return machine->getNoCoinState(); // Transition to NoCoinState
    }

    VendingState* refill(VendingMachine* machine, int productIdx, int quantity) override {
        cout << "Can't refill in this state." << endl;
        return machine->getHasCoinState(); // Stay in same state
    }

    string getStateName() override { 
        return "HAS_COIN"; 
    }
};

// Concrete State: Item Sold
class DispenseState : public VendingState {
public:
    VendingState* insertCoin(VendingMachine* machine, int coin) override {
       cout << "Please wait, already dispensing item. Coin returned: Rs " << coin <<endl;
        return machine->getDispenseState();  // Stay in same state
    }
    
    VendingState* selectItem(VendingMachine* machine, int productIdx) override {
        cout << "Already dispensing item. Please wait." <<endl;
        return machine->getDispenseState(); // Stay in same state
    }

    VendingState* dispense(VendingMachine* machine) override {
        Product& prod = machine->getSelectedProduct();
        cout << "Item '" << prod.name << "' dispensed!" << endl;
        machine->decrementSelectedProduct();
        if (machine->allSoldOut()) {
            cout << "Machine is now sold out!" << endl;
            return machine->getSoldOutState();
        }
        return machine->getNoCoinState();
    }
    
    VendingState* returnCoin(VendingMachine* machine) override {
       cout << "Cannot return coin while dispensing item!" <<endl;
        return machine->getDispenseState(); // Stay in same state
    }

    VendingState* refill(VendingMachine* machine, int productIdx, int quantity) override {
        cout << "Can't refil in this state" <<endl;
        return machine->getDispenseState(); // Stay in same state
    }

   string getStateName() override {
        return "DISPENSING";
    }
};

// Concrete State: Sold Out
class SoldOutState : public VendingState {
public:
    VendingState* insertCoin(VendingMachine* machine, int coin) override {
       cout << "Machine is sold out. Coin returned: Rs " << coin <<endl;
        return machine->getSoldOutState(); // Stay in same state
    }
    
    VendingState* selectItem(VendingMachine* machine, int productIdx) override {
        cout << "Machine is sold out!" <<endl;
        return machine->getSoldOutState(); // Stay in same state
    }
    
    VendingState* dispense(VendingMachine* machine) override {
       cout << "Machine is sold out!" <<endl;
        return machine->getSoldOutState(); // Stay in same state
    }
    
    VendingState* returnCoin(VendingMachine* machine) override {
       cout << "Machine is sold out. No coin inserted." <<endl;
        return machine->getSoldOutState(); // Stay in same state
    }
    
    VendingState* refill(VendingMachine* machine, int productIdx, int quantity) override {
        cout << "Refilling product " << machine->getProducts()[productIdx].name << endl;
        machine->incrementProductQuantity(productIdx, quantity);
        return machine->getNoCoinState();
    }
    
   string getStateName() override {
        return "SOLD_OUT";
    }
};

// VendingMachine implementation (after all classes are defined)
VendingMachine::VendingMachine(vector<Product> prods) : products(prods), insertedCoins(0), selectedProductIdx(0) {
    noCoinState = new NoCoinState();
    hasCoinState = new HasCoinState();
    dispenseState = new DispenseState();
    soldOutState = new SoldOutState();
    currentState = allSoldOut() ? soldOutState : noCoinState;
}

void VendingMachine::insertCoin(int coin) { 
    currentState = currentState->insertCoin(this, coin); 
}

void VendingMachine::selectItem(int productIdx) { 
    currentState = currentState->selectItem(this, productIdx); 
}

void VendingMachine::dispense() { 
    currentState = currentState->dispense(this); 
}

void VendingMachine::returnCoin() {
    currentState = currentState->returnCoin(this);
}

void VendingMachine::refill(int productIdx, int quantity) { 
    currentState = currentState->refill(this, productIdx, quantity); 
}

void VendingMachine::printStatus() {
    cout << "\n--- Vending Machine Status ---" << endl;
    cout << "Inserted coin: Rs " << insertedCoins << endl;
    cout << "Products:" << endl;
    for (int i = 0; i < products.size(); ++i) {
        cout << " [" << i << "] " << products[i].name << " | Rs " << products[i].price << " | Qty: " << products[i].quantity << endl;
    }
    cout << "Current state: " << currentState->getStateName() << endl << endl;
}

bool VendingMachine::allSoldOut() {
    for (const auto& p : products)
        if (p.quantity > 0) return false;
    return true;
}

int main() {
    vector<Product> products = {
        Product("Water Bottle", 20, 2),
        Product("Soda", 25, 1),
        Product("Juice", 30, 0)
    };
    VendingMachine machine(products);
    machine.printStatus();

    cout << "1. Trying to select 'Soda' (idx 1) without coin:" << endl;
    machine.selectItem(1);
    machine.printStatus();

    cout << "2. Inserting coin (Rs 15):" << endl;
    machine.insertCoin(15);
    machine.printStatus();

    cout << "3. Selecting 'Soda' with insufficient funds:" << endl;
    machine.selectItem(1);
    machine.printStatus();

    cout << "4. Adding more coins (Rs 10):" << endl;
    machine.insertCoin(10);
    machine.printStatus();

    cout << "5. Selecting 'Soda' now (should dispense):" << endl;
    machine.selectItem(1);
    machine.printStatus();

    cout << "6. Dispense operation:" << endl;
    machine.dispense();
    machine.printStatus();

    cout << "7. Try buying 'Water Bottle' (idx 0):" << endl;
    machine.insertCoin(20);
    machine.selectItem(0);
    machine.dispense();
    machine.printStatus();

    cout << "8. Try buying 'Juice' (idx 2, sold out):" << endl;
    machine.insertCoin(30);
    machine.selectItem(2);
    machine.printStatus();

    cout << "9. Refill 'Juice':" << endl;
    machine.refill(2, 3);
    machine.printStatus();

    cout << "10. Try buying 'Juice' after refill:" << endl;
    machine.insertCoin(30);
    machine.selectItem(2);
    machine.dispense();
    machine.printStatus();

    return 0;
}