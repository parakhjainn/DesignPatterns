#include "RequestHandler.h"
#include "../DTO/request.h"
#include <iostream>

using namespace std;

class ValidateParamsHandler : public RequestHandler {
    RequestHandler* nextHandler;

public:
    ValidateParamsHandler(RequestHandler* nextHandler) {
        this -> nextHandler = nextHandler;
    }

    void handle(Request& request) override {
        cout << "ValidateParamsHandler: Validating the request body" << endl;

        this->nextHandler->handle(request);
        
    }
};
