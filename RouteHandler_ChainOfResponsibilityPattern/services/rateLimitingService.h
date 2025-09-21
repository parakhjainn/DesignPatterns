#include <iostream>
using namespace std;

class RateLimitingService {
public:
    virtual ~RateLimitingService() = default;
    virtual void doRateLimiting() = 0; // Pure virtual function
};