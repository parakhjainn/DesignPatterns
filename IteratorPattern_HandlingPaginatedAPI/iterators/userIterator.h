#include <vector>
#include "../repositories/userRepositoryImpl.h"
#include "iterator.h"

using namespace std;

class UserIterator : public Iterator<vector<string>> {
private:
    UserRepositoryImpl userRepository;
    int limit = 1;
    int offset = 0;
    vector<string> current;

public:
    UserIterator(int limit) : userRepository(), limit(limit), offset(0) 
    {
        current = userRepository.findUsers(limit, offset);
    }

    bool hasNext() override {
        return !current.empty();
    }

    vector<string> next() override {
        vector<string> result = current;
        this->offset += limit;
        this->current = userRepository.findUsers(limit, offset);
        return result;
    }
};