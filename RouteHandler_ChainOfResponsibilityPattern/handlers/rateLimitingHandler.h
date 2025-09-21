#include "requestHandler.h"
#include "../DTO/request.h"
#include "../services/rateLimitingService.h"
#include <iostream>

using namespace std;

class RateLimitingHandler : public RequestHandler {
private:
    RequestHandler* nextHandler;
    RateLimitingService* rateLimitingService;

public:
    RateLimitingHandler(RequestHandler* nextHandler, RateLimitingService* rateLimitingService) {
        this -> nextHandler = nextHandler;
        this -> rateLimitingService = rateLimitingService;
    }

    void handle(Request& request) override {
        rateLimitingService->doRateLimiting();
        cout << "This is a Rate Limiting Handler" << endl;
        this->nextHandler->handle(request);
    }
};