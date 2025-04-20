#include "UAV.h"
#include "Task.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

UAV::UAV(int id, double weightCapacity, double energyCapacity, 
         double posX, double posY)
    : id(id), 
      weightCapacity(weightCapacity), 
      energyCapacity(energyCapacity),
      currentEnergy(energyCapacity),
      posX(posX), posY(posY),
      hasTask(false),
      currentTaskWeight(0.0) {
    
    if (id <= 0) {
        throw std::invalid_argument("UAV ID must be positive");
    }
    if (weightCapacity <= 0 || energyCapacity <= 0) {
        throw std::invalid_argument("Capacities must be positive");
    }
}

double UAV::distanceTo(double x, double y) const {
    double dx = posX - x;
    double dy = posY - y;
    double value = ::hypot(dx, dy); 
    return value;// More numerically stable than sqrt(dx*dx + dy*dy)
}

void UAV::updateEnergy(double energyCost) {
    if (energyCost < 0) {
        throw std::invalid_argument("Energy cost cannot be negative");
    }
    currentEnergy -= energyCost;
    if (currentEnergy < 0) {
        currentEnergy = 0;
        std::cerr << "Warning: UAV " << id << " energy depleted!\n";
    }
}

void UAV::refuel() {
    currentEnergy = energyCapacity;
    std::cout << "UAV " << id << " refueled to full capacity (" 
              << energyCapacity << " units)\n";
}

void UAV::setPosition(double x, double y) {
    posX = x;
    posY = y;
}

bool UAV::canCarry(double weight) const {
    return !hasTask && (weight <= weightCapacity);
}

bool UAV::canReach(double x, double y, double returnEnergy) const {
    double distance = distanceTo(x, y);
    return (currentEnergy >= (distance + returnEnergy));
}

bool UAV::needsRefuel(double threshold) const {
    return (currentEnergy < threshold);
}

// Getters implementation
int UAV::getId() const { return id; }
double UAV::getWeightCapacity() const { return weightCapacity; }
double UAV::getEnergyCapacity() const { return energyCapacity; }
double UAV::getCurrentEnergy() const { return currentEnergy; }
double UAV::getPosX() const { return posX; }
double UAV::getPosY() const { return posY; }

void UAV::assignTask(const Task& task) {
    if (hasTask) {
        throw std::runtime_error("UAV already has a task");
    }
    hasTask = true;
    currentTaskWeight = task.getWeight(); 
}

void UAV::completeCurrentTask() {
    hasTask = false;
    currentTaskWeight = 0.0;
}