#include <vector>
#include <string>

using namespace std;

class InMemoryDatabase {
private:
    vector<string> users;

public:
    void seeder() {
        for (int i = 1; i <= 2000; ++i) {
            users.push_back("User " + to_string(i));
        }
    }

    const vector<string>& getUsers() const {
        return users;
    }
};