#include <iostream>
#include <vector>
#include <ctime>
#include "user.h"
#include "task.h"
#include "taskManagerService.h"

using namespace std;

int main() {
    // Get TaskManager instance
    TaskManager& taskManager = TaskManager::getInstance();

    // Create users
    User user1("1", "John Doe", "john@example.com");
    User user2("2", "Jane Smith", "jane@example.com");

    // Create tasks
    Task task1(1, "Task 1", "Description 1", time(nullptr), 1, &user1);
    Task task2(2, "Task 2", "Description 2", time(nullptr), 2, &user2);
    Task task3(3, "Task 3", "Description 3", time(nullptr), 1, &user1);

    // Add tasks to the task manager
    taskManager.createTask(task1);
    taskManager.createTask(task2);
    taskManager.createTask(task3);
    cout << "Created 3 tasks" << endl;

    // Update a task
    task2.setDescription("Updated description");
    taskManager.updateTask(task2);
    cout << "Updated task 2" << endl;

    // Search tasks
    vector<Task> searchResults = taskManager.searchTasks("Task");
    cout << "\nSearch Results:" << endl;
    for (const Task& task : searchResults) {
        cout << "  - " << task.getTitle() << endl;
    }

    // Mark a task as completed
    taskManager.markTaskAsCompleted(1);
    cout << "\nMarked task 1 as completed" << endl;

    // Get task history for a user
    vector<Task> taskHistory = taskManager.getTaskHistory(user1);
    cout << "\nTask History for " << user1.getName() << ":" << endl;
    for (const Task& task : taskHistory) {
        cout << "  - " << task.getTitle() << endl;
    }

    // Delete a task
    taskManager.deleteTask(3);
    cout << "\nDeleted task 3" << endl;

    // Verify deletion
    vector<Task> remainingTasks = taskManager.searchTasks("Task");
    cout << "\nRemaining tasks after deletion:" << endl;
    for (const Task& task : remainingTasks) {
        cout << "  - " << task.getTitle() << endl;
    }

    return 0;
}
