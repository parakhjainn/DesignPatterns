#include "../handlers/ValidateParamsHandler.h"
#include "../handlers/ValidateBodyHandler.h"
#include "../handlers/AuthorisationHandler.h"
#include "../handlers/AuthenticationHandler.h"
#include "../handlers/FinishingHandler.h"
#include "../handlers/HandlerB.h"
#include "../services/tokenServiceImpl.h"

class RequestHandlerFactory {
public:
    static RequestHandler* getHandlersForCreateTodo() {
        // We can add another handler like handlerB in between any handlers as needed
        // We can change the order of handlers as needed
        // We can also skip some handlers as needed

        // params -> body -> authorisation -> authentication -> finishing
        auto* finishing = new FinishingHandler();
        auto* tokenService = new TokenServiceImpl();
        auto* authentication = new AuthenticationHandler(finishing, tokenService);
        auto* authorisation = new AuthorisationHandler(authentication);
        auto* validateBody = new ValidateBodyHandler(authorisation);
        auto* validateParams = new ValidateParamsHandler(validateBody);
        return validateParams;
        // If we want to add rate limiting handler, we can do it here
        // auto* rateLimiting = new RateLimitingHandler(validateParams);
        // return rateLimiting;
    }

    static RequestHandler* getHandlerForUpdateTodo() {
        // body -> params -> authentication -> authorisation -> finishing
        auto* finishing = new FinishingHandler();
        auto* tokenService = new TokenServiceImpl();
        auto* authorisation = new AuthenticationHandler(finishing, tokenService);
        auto* authentication = new AuthorisationHandler(authorisation);
        auto* validateParams = new ValidateBodyHandler(authentication);
        auto* validateBody = new ValidateParamsHandler(validateParams);
        return validateBody;
        // If we want to add rate limiting handler, we can do it here
        // auto* rateLimiting = new RateLimitingHandler(validateBody);
        // return rateLimiting;
    }
};