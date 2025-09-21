#include "../DTO/request.h"

// Interface for all token services
class TokenService {
public:
    virtual ~TokenService() = default;
    virtual bool validateToken(Request& request) = 0; // Pure virtual function
};