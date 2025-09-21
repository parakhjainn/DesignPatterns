#include<iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "userRepository.h"
#include "../InMemoryDatabase.h"

using namespace std;

class UserRepositoryImpl : public UserRepository {
private:
    InMemoryDatabase db;

public:
    UserRepositoryImpl(InMemoryDatabase& database) : db(database) 
    {
        db.seeder(); // Seed the database with initial data
    }

    vector<string> findUsers(int limit, int offset) override {
        vector<string>& allUsers = db.getUsers();
        int start = (offset - 1) * limit;                // start of the paginated data
        int end = min(start + limit, allUsers.size());   // end of the paginated data

        if (start >= allUsers.size() || start < 0) {
            return {};
        }

        return vector<string>(allUsers.begin() + start, allUsers.begin() + end);
    }
};

/**
 *  When limit and offset based pagination is not good
 *
 *  f10, f9, f8, f7, f6, f5, f4, f3, f2, f1
 *  limit=3, offset=0 -> f10, f9, f8 (first 3 posts)
 *
 *  f12, f11, f10, f9, f8, f7, f6, f5, f4, f3, f2, f1
 *  limit=3, offset=3 -> Expected output(f7, f6, f5) but actual output(f9, f8, f7)
 *
 *  Solution - Cursor based pagination
 *  SELECT * from posts where createdAt < t8 order by createdAt desc limit 3
 */
