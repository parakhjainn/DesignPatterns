#include "tokenService.h"
#include "../DTO/request.h"
#include <iostream>

using namespace std;

class RateLimitingServiceImpl : public RateLimitingService {
public:

    void doRateLimiting() override {
        cout << "RateLimitingServiceImpl: Rate Limiting Algo\n";
    }
};