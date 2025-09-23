#include <iostream>
#include <vector>
#include "../repositories/userRepositoryImpl.h"
#include "../iterators/userIterator.h"

using namespace std;

class UserService {
private:
    UserRepository userRepository;
    Iterator<vector<string>> userIterator;

public:
    UserService(UserRepositoryImpl userRepositoryImpl) {
        this -> userRepository = userRepositoryImpl;
        this -> userIterator = UserIterator(10);
    }

    void getUsersOnPlatform() {
        // this->userRepository.findUsers(10, 1);
        /** this->userRepository.findUsers(10, 1);
            * 1. Here the Service layer has to keep track of current offset
            * 2. Wherever this pagination is reqd, we need to maintain offset there
            * 3. We don't know when to stop ? We might have to write a custom logic, to check if no more data is there
        */

        while (userIterator.hasNext()) {
            vector<string> users = userIterator.next();
            for (const auto& user : users) {
                cout << user << endl;
            }
        }
    }
};
