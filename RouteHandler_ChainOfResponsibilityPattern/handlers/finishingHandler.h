#include "RequestHandler.h"
#include "../DTO/request.h"
#include <iostream>

using namespace std;

class FinishingHandler : public RequestHandler {
public:

    void handle(Request& request) override {
        cout << "Finishing the request" << endl;
    }
};
