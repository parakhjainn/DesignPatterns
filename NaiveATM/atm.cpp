#include<iostream>
#include<string>
#include<random>
using namespace std;

class ATM {
public:
    // Enum for ATM states
    enum ATMState {
        IDLE, TRANSACTION_IN_PROGRESS, CARD_INSERTED, AMOUNT_ENTERED, DISPENSING_CASH
    };  

private:
    string atmId;        // Unique identifier for the ATM
    ATMState state;      // Current state of the ATM

public:
    // Constructor
    ATM(string atmId) : atmId(atmId), state(IDLE) {} // Default state is IDLE           

    // Start a transaction
    int startTransaction() {
        if (state != IDLE) {
            throw runtime_error("ATM is currently busy with another transaction.");
        }
        state = TRANSACTION_IN_PROGRESS;
        int transactionId = generateTransactionId();
        cout << "Transaction started with ID: " << transactionId << " on ATM: " << atmId << endl;
        return transactionId;
    }       

    // Cancel a transaction
    void cancelTransaction() {
        if (state == IDLE) {    
            throw runtime_error("No transaction to cancel.");
        }
        state = IDLE;
        cout << "Transaction canceled on ATM: " << atmId << endl;
    }           

    // Read card details and validate
    bool readCard(string cardType, long cardNumber, int pin) {
        if (state != TRANSACTION_IN_PROGRESS) {
            throw runtime_error("Cannot read card. Start a transaction first.");
        }
        state = CARD_INSERTED;
        bool isValid = validateCardDetails(cardType, cardNumber, pin);
        if (!isValid) {
            state = IDLE;
        }
        return isValid;
    }

    // Enter withdrawal amount
    bool enterAmount(double amount) {
        if (state != CARD_INSERTED) {
            throw runtime_error("Card must be inserted before entering an amount.");
        }
        state = AMOUNT_ENTERED;
        return checkWithdrawalLimit(amount);
    }   

    // Dispense cash
    void dispenseCash(double amount) {
        if (state != AMOUNT_ENTERED) {
            throw runtime_error("Amount must be entered before dispensing cash.");
        }
        state = DISPENSING_CASH;
        cout << "Dispensing cash: " << amount << " on ATM: " << atmId << endl;
        state = IDLE; // Reset state after dispensing
    }   

    // Eject card
    void ejectCard() {
        if (state == IDLE) {
            throw runtime_error("No card to eject.");
        }
        state = IDLE;
        cout << "Card ejected from ATM: " << atmId << endl;
    }

private:
    // Private helper methods
    int generateTransactionId() {
        return (int) (random() * 100000); // Generate random transaction ID
    }   

    bool validateCardDetails(string cardType, long cardNumber, int pin) {
        // Simulate card validation
        return true; // Assume valid for simplicity
    }

    bool checkWithdrawalLimit(double amount) {
        // Simulate withdrawal limit check
        return amount <= 1000; // Assume a max limit of 1000
    }
};  