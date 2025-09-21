#include "RequestHandler.h"
#include "../DTO/request.h"
#include "../services/TokenService.h"
#include <iostream>

using namespace std;

class AuthorisationHandler : public RequestHandler {
private:
    RequestHandler* nextHandler;

public:
    AuthorisationHandler(RequestHandler* nextHandler) {
        this->nextHandler = nextHandler;
    }

    void handle(Request& request) override {
        tokenService->validateToken(request);
        cout << "AuthorisationHandler: Authorising the request\n";
        
        this->nextHandler->handle(request);      
    }
};


