#include<iostream>
#include<string>
#include"enums/cardType.h"

using namespace std;

class Card {
private:
    long cardNumber;
    int pin;
    string name;
    CardType cardType;
    string bankName;    
public:
    Card(long cardNumber, int pin, string name, CardType cardType, string bankName) {
        this->cardNumber = cardNumber;
        this->pin = pin;
        this->name = name;
        this->cardType = cardType;
        this->bankName = bankName;
    }   

    long getCardNumber() {
        return cardNumber;
    }

    int getPin() {
        return pin;
    }

    string getName() {
        return name;
    }

    CardType getCardType() {
        return cardType;
    }

    string getBankName() {
        return bankName;
    }

    // toString
    string toString() {
        return "Card{cardNumber=" + to_string(cardNumber) + ", pin=" + to_string(pin) + ", name=" + name + ", cardType=" + to_string(cardType) + ", bankName=" + bankName + "}";
    }
}; 
