#include "../DTO/request.h"

using namespace std;

// Interface for all handlers
class RequestHandler {
public:
    virtual ~RequestHandler() = default;
    // what to do in a handler goes here
    virtual void handle(Request& request) = 0; // Pure virtual function
};