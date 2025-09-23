#include<iostream>

using namespace std;

class UserService {
public:
    virtual User getUserById(const string& userId) = 0;
    virtual ~UserService() = default;
};