#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "UAV.h"
#include "Task.h"

class Scheduler {
public:
    Scheduler(double refuelThreshold, double refuelStationX, double refuelStationY);
    
    // Enhanced interface
    void allocateTasks();
    void checkRefuel();
    void printStatus() const;
    
    // Task management
    void addTask(const Task& task);
    void clearTasks();
    
    // UAV management
    void addUAV(const UAV& uav);
    void clearUAVs();
    
    // Configuration
    void setRefuelStation(double x, double y);
    
    // Public members (consider making private with accessors)
    std::vector<UAV> uavs;
    std::vector<Task> tasks;

private:
    // Improved helper methods
    double computePriority(const UAV& uav, const Task& task) const;
    bool canReachWithReturn(const UAV& uav, const Task& task) const;
    void assignTaskToUAV(UAV& uav, Task& task);
    void returnToBase(UAV& uav);
    
    // Configuration
    double refuelThreshold;
    double refuelStationX;
    double refuelStationY;
    
    // Statistics
    mutable unsigned int tasksAssigned;
};

#endif // SCHEDULER_H