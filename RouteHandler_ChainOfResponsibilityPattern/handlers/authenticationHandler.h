#include "RequestHandler.h"
#include "../DTO/request.h"
#include "../services/TokenService.h"
#include <iostream>

using namespace std;

class AuthenticationHandler : public RequestHandler {
private:
    RequestHandler* nextHandler;
    TokenService* tokenService;

public:
    AuthenticationHandler(RequestHandler* nextHandler, TokenService* tokenService) {
        this->nextHandler = nextHandler;
        this->tokenService = tokenService;
    }

    void handle(Request& request) override {
        tokenService->validateToken(request);
        cout << "AuthenticationHandler: Authenticating the request\n";
        
        this->nextHandler->handle(request);      
    }
};