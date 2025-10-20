#include <string>
#include <random>
#include <sstream>
#include <iomanip>
#include "balanceSheet.h"

using namespace std;

class User {
    string id;
    string name;
    string email;
    BalanceSheet* balanceSheet;
    
public:
    User(string& name, string& email)
        : id("random id"), 
          name(name), 
          email(email),
          balanceSheet(new BalanceSheet(this)) {
    }
    
    ~User() {
        delete balanceSheet;
    }
    
    string& getId() {
        return id;
    }
    
    string& getName() {
        return name;
    }
    
    BalanceSheet* getBalanceSheet() {
        return balanceSheet;
    }
};
