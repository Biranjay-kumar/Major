//schedular.cpp

#include "Scheduler.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits>

Scheduler::Scheduler(double refuelThreshold, double refuelStationX, double refuelStationY)
    : refuelThreshold(refuelThreshold), 
      refuelStationX(refuelStationX), 
      refuelStationY(refuelStationY),
      tasksAssigned(0) {
    
    if (refuelThreshold <= 0) {
        throw std::invalid_argument("Refuel threshold must be positive");
    }
}

void Scheduler::assignTasks() {
    // Iterate through the tasks
    for (auto& task : tasks) {
        bool assigned = false;
        
        // Check UAV fleet to find an eligible UAV
        for (auto& uav : uavs) {
            if (uav.canCarry(task.getWeight()) && uav.canReach(task.getX(), task.getY())) {
                // Assign the task if the UAV can carry and reach it
                uav.assignTask(task);
                std::cout << "Assigned Task " << task.getId() << " to UAV " << uav.getId() << std::endl;
                assigned = true;
                break; // Task assigned, exit UAV loop
            }
        }
        
        if (!assigned) {
            std::cout << "No UAV available for Task " << task.getId() << std::endl;
        }
    }
}

double Scheduler::computePriority(const UAV &uav, const Task &task) const {
    const double dist = uav.distanceTo(task.getPosX(), task.getPosY());
    const double currentValue = task.getCurrentValue(0); // Assuming time=0 for demo
    const double urgency = 1.0 / (task.getDeadline() + 1.0); // Deadline urgency factor
    return (currentValue * urgency) / (dist + 1.0); // Multi-factor priority
}

bool Scheduler::canReachWithReturn(const UAV& uav, const Task& task) const {
    const double taskDist = uav.distanceTo(task.getPosX(), task.getPosY());
    const double returnDist = task.distanceTo(refuelStationX, refuelStationY);
    return (uav.getCurrentEnergy() >= (taskDist + returnDist));
}

void Scheduler::assignTaskToUAV(UAV& uav, Task& task) {
    const double travelCost = uav.distanceTo(task.getPosX(), task.getPosY());
    uav.updateEnergy(-travelCost);
    uav.setPosition(task.getPosX(), task.getPosY());
    task.markCompleted();
    
    std::cout << "ASSIGN: UAV " << uav.getId() 
              << " → Task " << task.getId()
              << " (Cost: " << travelCost 
              << ", Remaining Energy: " << uav.getCurrentEnergy() << ")\n";
    
    tasksAssigned++;
}

void Scheduler::returnToBase(UAV& uav) {
    const double returnDist = uav.distanceTo(refuelStationX, refuelStationY);
    uav.updateEnergy(-returnDist);
    uav.setPosition(refuelStationX, refuelStationY);
    
    std::cout << "RETURN: UAV " << uav.getId()
              << " to base (Cost: " << returnDist
              << ", Remaining Energy: " << uav.getCurrentEnergy() << ")\n";
}

void Scheduler::allocateTasks() {
    tasksAssigned = 0;
    
    for (auto &uav : uavs) {
        bool canContinue = true;
        
        while (canContinue && uav.getCurrentEnergy() > refuelThreshold) {
            auto bestTaskIter = std::max_element(tasks.begin(), tasks.end(),
                [&](const Task& a, const Task& b) {
                    if (a.isCompleted() != b.isCompleted()) 
                        return a.isCompleted();
                    return computePriority(uav, a) < computePriority(uav, b);
                });
                
            if (bestTaskIter != tasks.end() && !bestTaskIter->isCompleted() && 
                canReachWithReturn(uav, *bestTaskIter)) {
                assignTaskToUAV(uav, *bestTaskIter);
            } else {
                canContinue = false;
                if (uav.distanceTo(refuelStationX, refuelStationY) > 0) {
                    returnToBase(uav);
                }
            }
        }
    }
    
    std::cout << "Task allocation complete. Assigned " << tasksAssigned << " tasks.\n";
}

void Scheduler::checkRefuel() {
    for (auto &uav : uavs) {
        if (uav.getCurrentEnergy() < refuelThreshold) {
            std::cout << "REFUEL: UAV " << uav.getId() 
                      << " (Energy: " << uav.getCurrentEnergy() 
                      << " < " << refuelThreshold << ")\n";
                      
            if (uav.getPosX() != refuelStationX || uav.getPosY() != refuelStationY) {
                returnToBase(uav);
            }
            uav.refuel();
        }
    }
}