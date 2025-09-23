#include<NewUserService.h>
#include<userService.h>

class UserServiceAdaptor : public UserService {
    NewUserService newUserService;  

    User mapToUser(const UserResponse& response) {
        User user;
        user.setId(response.getId());
        user.setName(response.getName());
        user.setEmail(response.getEmail());
        return user;
    }

    void updateUserDetails(const User& user) {
        userService.updateUser(user);

        newUserService.UpdateUserDetails(user);

    }
public: 
    UserServiceAdaptor(NewUserService newUserService) : newUserService(newUserService) {}

    User getUserById(const string& userId) override {
        UserResponse response = newUserService.FetchUser(userId);
        return mapToUser(response);
    }
};