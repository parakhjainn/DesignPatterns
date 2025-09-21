#include "RequestHandler.h"
#include "../DTO/request.h"
#include <iostream>

using namespace std;

class ValidateBodyHandler : public RequestHandler {
    RequestHandler* nextHandler;

public:
    ValidateBodyHandler(RequestHandler* nextHandler) {
        this -> nextHandler = nextHandler;
    }

    void handle(Request& request) override {
        // Above the next handler call, whatever is written is executed before

        cout << "ValidateBodyHandler: Validating the request body" << endl;

        this->nextHandler->handle(request);

        // below the handler, whatever is written is executed after the next handler
    }
};
