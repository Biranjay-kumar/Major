#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "UAV.h"
#include "Task.h"

class Scheduler {
public:
    // Constructor
    Scheduler(double refuelThreshold, double refuelStationX, double refuelStationY);
    
    // Public methods for task and UAV management
    void addTask(const Task& task);            // Add a task to the scheduler
    void clearTasks();                         // Clear all tasks
    void addUAV(const UAV& uav);               // Add a UAV to the fleet
    void clearUAVs();                          // Clear all UAVs
    
    // Public methods for task allocation and refuel checks
    void allocateTasks();                      // Allocate tasks to UAVs
    void checkRefuel();                        // Check UAVs and refuel if necessary
    void printStatus() const;                  // Print the status of tasks and UAVs
    
    // Configuration methods
    void setRefuelStation(double x, double y); // Set refuel station position

    void assignTasks();  // Declare the function


private:
    // Helper methods for task management and UAV assignment
    double computePriority(const UAV& uav, const Task& task) const; // Compute task priority based on UAV capabilities
    bool canReachWithReturn(const UAV& uav, const Task& task) const; // Check if UAV can complete the task and return
    void assignTaskToUAV(UAV& uav, Task& task); // Assign task to a UAV
    void returnToBase(UAV& uav); // Return UAV to the base if energy is low

    // Private member variables (use accessors if needed)
    double refuelThreshold;
    double refuelStationX;
    double refuelStationY;
    
    std::vector<UAV> uavs;  // UAV fleet
    std::vector<Task> tasks; // Task list
    
    // Statistics
    mutable unsigned int tasksAssigned; // Number of tasks assigned to UAVs
};

#endif // SCHEDULER_H
