#include<iostream>
#include<string>

using namespace std;

class NewUserService {
public:
    UserResponse FetchUser(const string& userId) = 0;
    virtual ~NewUserService() = default;
};

class UserResponse {
    string id;
    string name;
    string email; 
};