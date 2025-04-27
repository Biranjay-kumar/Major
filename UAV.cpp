#include "UAV.h"
#include "Task.h"
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <limits>
#include <sstream>

// Platform-specific math definitions
#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif
#include <math.h>

// Fallback implementations
namespace {
    bool my_isnan(double x) {
        return x != x;  // Reliable NaN check
    }
    
    template<typename T>
    std::string my_to_string(T value) {
        std::ostringstream os;
        os << value;
        return os.str();
    }
}

UAV::UAV(int id, double weightCapacity, double energyCapacity,
         double posX, double posY)
    : id(id),
      weightCapacity(weightCapacity),
      energyCapacity(energyCapacity),
      currentEnergy(energyCapacity),
      posX(posX),
      posY(posY),
      hasTask(false),
      currentTaskWeight(0.0)
{
    validateConstructionParameters();
}

void UAV::validateConstructionParameters() const {
    if (id <= 0) {
        throw std::invalid_argument("UAV ID must be positive");
    }
    if (weightCapacity <= 0 || energyCapacity <= 0) {
        throw std::invalid_argument("Capacities must be positive");
    }
    if (my_isnan(posX) || my_isnan(posY)) {
        throw std::invalid_argument("Position coordinates must be valid numbers");
    }
}

double UAV::distanceTo(double x, double y) const {
    validateCoordinates(x, y);
    return ::hypot(posX - x, posY - y);
}

void UAV::validateCoordinates(double x, double y) const {
    if (my_isnan(x) || my_isnan(y)) {
        throw std::invalid_argument("Invalid coordinates provided");
    }
}

void UAV::updateEnergy(double energyCost) {
    if (my_isnan(energyCost)) {
        throw std::invalid_argument("Energy cost must be a valid number");
    }
    if (energyCost < 0) {
        throw std::invalid_argument("Energy cost cannot be negative");
    }
    
    currentEnergy -= energyCost;
    if (currentEnergy < 0) {
        currentEnergy = 0;
        throw std::runtime_error("UAV " + my_to_string(id) + " energy depleted!");
    }
}

void UAV::refuel() {
    currentEnergy = energyCapacity;
    std::cout << "UAV " << id << " refueled to full capacity ("
              << energyCapacity << " units)\n";
}

void UAV::setPosition(double x, double y) {
    validateCoordinates(x, y);
    posX = x;
    posY = y;
}

bool UAV::canCarry(double weight) const {
    if (weight < 0) {
        throw std::invalid_argument("Weight cannot be negative");
    }
    return !hasTask && (weight <= weightCapacity);
}

bool UAV::canReach(double x, double y, double returnEnergy) const {
    validateCoordinates(x, y);
    if (returnEnergy < 0) {
        throw std::invalid_argument("Return energy cannot be negative");
    }
    
    const double safetyMargin = energyCapacity * 0.05;
    double distance = distanceTo(x, y);
    return (currentEnergy >= (distance + returnEnergy + safetyMargin));
}

bool UAV::needsRefuel(double threshold) const {
    if (threshold < 0 || threshold > energyCapacity) {
        throw std::invalid_argument("Invalid refuel threshold");
    }
    return (currentEnergy < threshold);
}

void UAV::assignTask(const Task& task) {
    if (hasTask) {
        throw std::runtime_error("UAV already has a task");
    }
    if (!canCarry(task.getWeight())) {
        throw std::runtime_error("Task weight exceeds UAV capacity");
    }
    
    hasTask = true;
    currentTaskWeight = task.getWeight();
}

void UAV::completeCurrentTask() {
    if (!hasTask) {
        throw std::logic_error("No active task to complete");
    }
    hasTask = false;
    currentTaskWeight = 0.0;
}

void UAV::emergencyLand() {
    currentEnergy = 0;
    hasTask = false;
    currentTaskWeight = 0.0;
}

std::string UAV::getStatus() const {
    return "UAV " + my_to_string(id) + 
           " | Position: (" + my_to_string(posX) + ", " + my_to_string(posY) + ")" +
           " | Energy: " + my_to_string(currentEnergy) + "/" + my_to_string(energyCapacity) +
           " | " + (hasTask ? "Carrying task" : "Available");
}