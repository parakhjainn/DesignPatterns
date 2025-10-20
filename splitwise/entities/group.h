#include <string>
#include <vector>
#include <random>
#include <sstream>
#include "user.h"

using namespace std;

class Group {
    const string id;
    const string name;
    vector<User*> members;
    
public:
    Group(const string& name, const vector<User*>& members)
        : id(generateUUID()), 
          name(name), 
          members(members) {
    }
    
    const string& getId() const {
        return id;
    }
    
    const string& getName() const {
        return name;
    }
    
    vector<User*> getMembers() const {
        return members; // Returns a copy of the vector
    }
    
    ~Group() {
        delete members;
    }
};
