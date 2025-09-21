#include<iostream>
#include<vector>
#include<string>
using namespace std;

class UserRepository {
public:
    virtual ~UserRepository() = default;
    virtual vector<string> findUsers(int limit, int offset) = 0;
};