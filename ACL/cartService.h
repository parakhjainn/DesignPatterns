#include<userService.h>


class CartService {
    UserService userService;

public:
    CartService(UserService userService) {
        this->userService = userService;
    }

    void processCart(const string& userId) {
        User user = userService.getUserById(userId);
        // Process cart for the user
    }
};