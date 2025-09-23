#include<iostream>
using namespace std;

int main() {
    cout << "Adapter Design Pattern Example\n";

    NewUserService newUserService;/* instantiate concrete NewUserService implementation */

    UserService userServiceAdaptor = new UserServiceAdaptor(newUserService);

    CartService cartService(userServiceAdaptor); // old cart service using old user service only

    return 0;
}