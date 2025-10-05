#include <iostream>
#include <string>
#include "state.h"
#include "models/atm.h"
#include "models/card.h"
#include "enums/atmState.h"
#include "apis/backendAPI.h"
#include "apis/nodeBackendAPI.h"
#include "state/readCardDetailsAndPinState.h"
#include "dto/createTransactionRequestDTO.h"

using namespace std;

class ReadyForTransactionState : public State {
private:
    ATM* atm;
    BackendAPI* backendAPI; 
public:
    ReadyForTransactionState(ATM* atm) : atm(atm) {
        backendAPI = new NodeBackendAPI();
    }   

    int initTransaction() override {
        CreateTransactionRequestDTO createTransactionDTO(atm->getAtmId());

        int transactionId = backendAPI->createTransaction(createTransactionDTO);

        if (transactionId == 0) {
            throw runtime_error("Transaction could not be created");
        }

        // Now that we have the transactionId from the backend, we should move the ATM to the next state
        atm->changeState(new ReadCardDetailsAndPinState(atm));
        return transactionId;
    }

    bool readCardDetailsAndPin(Card card, string pin) override {
        throw runtime_error("Cannot read card details and pin without inserting card");
    }

    int dispenseCash(Card card, int amount, int transactionId) override {
        throw runtime_error("Cannot dispense cash without reading card details and pin");
    }

    void ejectCard() override {
        throw runtime_error("Cannot eject card without reading card details and pin");
    }

    bool readCashWithdrawDetails(Card card, int transactionId, int amount) override {
        throw runtime_error("Cannot read cash withdraw details without reading card details and pin");
    }

    bool cancelTransaction(int transactionId) override {
        throw runtime_error("Cannot cancel transaction without reading card details and pin");
    }

    ATMState getState() override {
        return ATMState::READY_FOR_TRANSACTION;
    }

    ~ReadyForTransactionState() {
        delete backendAPI;
    }

};