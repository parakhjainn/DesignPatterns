package IteratorPattern_HandlingPaginatedAPI.services;

import IteratorPattern_HandlingPaginatedAPI.iterators.Iterator;
import IteratorPattern_HandlingPaginatedAPI.iterators.UserIterator;
import IteratorPattern_HandlingPaginatedAPI.repositories.UserRepository;
import IteratorPattern_HandlingPaginatedAPI.repositories.UserRepositoryImpl;

import java.util.List;

public class UserService {

    private final UserRepository userRepository;
    private final Iterator<List<String>> userIterator;

    public UserService(UserRepository userRepository) {
        this.userRepository = new UserRepositoryImpl();
        this.userIterator = new UserIterator(10);
    }

    public void getUsersOnPlatform() {

        
        while(userIterator.hasNext()) {
            List<String> users = userIterator.next();
            System.out.println(users);
        }

    }
}


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
