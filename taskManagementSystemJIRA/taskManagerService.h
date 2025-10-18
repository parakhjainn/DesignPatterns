#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <algorithm>
#include <ctime>
#include "task.h"

using namespace std;

class TaskManager {
    unordered_map<int, Task> tasks;
    unordered_map<string, vector<Task>> userTasks;
    mutex mtx;

    TaskManager() {}

public:
    static TaskManager& getInstance() {
        static TaskManager instance;
        return instance;
    }

    void createTask(const Task& task) {
        lock_guard<mutex> lock(mtx);
        tasks.insert({task.getId(), task});
        assignTaskToUserInternal(task.getAssignedUser(), task);
    }

    void updateTask(const Task& updatedTask) {
        lock_guard<mutex> lock(mtx);
        auto it = tasks.find(updatedTask.getId());
        if (it != tasks.end()) {
            Task& existingTask = it->second;
            User* previousUser = existingTask.getAssignedUser();
            User* newUser = updatedTask.getAssignedUser();
            
            existingTask.setTitle(updatedTask.getTitle());
            existingTask.setDescription(updatedTask.getDescription());
            existingTask.setDueDate(updatedTask.getDueDate());
            existingTask.setPriority(updatedTask.getPriority());
            existingTask.setStatus(updatedTask.getStatus());
            existingTask.setAssignedUser(newUser);
            
            if (previousUser != newUser) {
                unassignTaskFromUserInternal(previousUser, existingTask);
                assignTaskToUserInternal(newUser, existingTask);
            }
        }
    }

    void deleteTask(int taskId) {
        lock_guard<mutex> lock(mtx);
        auto it = tasks.find(taskId);
        if (it != tasks.end()) {
            Task task = it->second;
            tasks.erase(it);
            unassignTaskFromUserInternal(task.getAssignedUser(), task);
        }
    }

    vector<Task> searchTasks(const string& keyword) {
        lock_guard<mutex> lock(mtx);
        vector<Task> matchingTasks;
        for (const auto& pair : tasks) {
            const Task& task = pair.second;
            if (task.getTitle().find(keyword) != string::npos || 
                task.getDescription().find(keyword) != string::npos) {
                matchingTasks.push_back(task);
            }
        }
        return matchingTasks;
    }

    void markTaskAsCompleted(int taskId) {
        lock_guard<mutex> lock(mtx);
        auto it = tasks.find(taskId);
        if (it != tasks.end()) {
            it->second.setStatus(TaskStatus::COMPLETED);
        }
    }

    vector<Task> getTaskHistory(const User& user) {
        lock_guard<mutex> lock(mtx);
        auto it = userTasks.find(user.getId());
        if (it != userTasks.end()) {
            return it->second;
        }
        return vector<Task>();
    }

private:
    // Internal methods - assume lock is already held
    void assignTaskToUserInternal(User* user, const Task& task) {
        userTasks[user->getId()].push_back(task);
    }

    void unassignTaskFromUserInternal(User* user, const Task& task) {
        auto it = userTasks.find(user->getId());
        if (it != userTasks.end()) {
            auto& taskList = it->second;
            taskList.erase(remove_if(taskList.begin(), taskList.end(),
                [&task](const Task& t) { return t.getId() == task.getId(); }),
                taskList.end());
        }
    }
};
