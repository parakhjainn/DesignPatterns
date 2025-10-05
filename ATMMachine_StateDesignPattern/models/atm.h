#include <iostream>
#include <string>
#include "state/state.h"
#include "state/readyForTransactionState.h"
#include "apis/backendAPI.h"
#include "apis/nodeBackendAPI.h"
#include "dto/updateATMStateRequestDTO.h"

using namespace std;

class ATM {
private:
    string atmId;
    State* state;
    BackendAPI* backendAPI;
public:
    ATM(string atmId) {
        this->atmId = atmId;
        this->backendAPI = new NodeBackendAPI();
        this->state = new ReadyForTransactionState(this);
    }   

    string getAtmId() {
        return atmId;
    }

    void changeState(State* newState) {
        this->state = newState;
        // now call the server to persist the state on the server also
        this->backendAPI->updateState(UpdateATMStateRequestDTO(this->atmId, newState->getState()));
    }
    
};