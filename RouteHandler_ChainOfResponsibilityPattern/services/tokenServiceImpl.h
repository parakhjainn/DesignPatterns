#include "tokenService.h"
#include "../DTO/request.h"
#include <iostream>

using namespace std;

class TokenServiceImpl : public TokenService {
public:

    bool validateToken(Request& request) override {
        cout << "TokenServiceImpl: Validating token\n";
        // fetches token from header
        // if token is not found return 404 token missing
        // validates the token using the key
        // if token is invalid then return not authenticated
        return true;
    }
};