#include "../DTO/Request.h"
#include "../factory/RequestHandlerFactory.h"
#include "../schema/Todo.h"

class TodoController {
private:
    Todo createTodo(Request& request) {
        // execute initial handler
        RequestHandlerFactory::getHandlersForCreateTodo()->handle(request);
        
        // return a new todo
        return Todo();
    }
};