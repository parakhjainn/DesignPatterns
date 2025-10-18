#pragma once

#include <string>
#include <ctime>
#include "user.h"

using namespace std;

enum class TaskStatus {
    PENDING,
    IN_PROGRESS,
    COMPLETED
};

class Task {
private:
    int id;
    string title;
    string description;
    time_t dueDate;
    int priority;
    User* assignedUser;
    TaskStatus status;

public:
    // Add default constructor
    Task() 
        : id(0), 
          title(""), 
          description(""), 
          dueDate(0), 
          priority(0), 
          assignedUser(nullptr),
          status(TaskStatus::PENDING) {
    }

    // Constructor
    Task(int id, const string& title, const string& description, 
         time_t dueDate, int priority, User* assignedUser)
        : id(id), 
          title(title), 
          description(description), 
          dueDate(dueDate), 
          priority(priority), 
          assignedUser(assignedUser),
          status(TaskStatus::PENDING) {
    }
    
    // Getters
    int getId() const {
        return id;
    }
    
    string getTitle() const {
        return title;
    }
    
    string getDescription() const {
        return description;
    }
    
    time_t getDueDate() const {
        return dueDate;
    }
    
    int getPriority() const {
        return priority;
    }
    
    TaskStatus getStatus() const {
        return status;
    }
    
    User* getAssignedUser() const {
        return assignedUser;
    }
    
    // Setters
    void setId(int newId) {
        id = newId;
    }
    
    void setTitle(const string& newTitle) {
        title = newTitle;
    }
    
    void setDescription(const string& newDescription) {
        description = newDescription;
    }
    
    void setDueDate(time_t newDueDate) {
        dueDate = newDueDate;
    }
    
    void setPriority(int newPriority) {
        priority = newPriority;
    }
    
    void setStatus(TaskStatus newStatus) {
        status = newStatus;
    }
    
    void setAssignedUser(User* newAssignedUser) {
        assignedUser = newAssignedUser;
    }
};
