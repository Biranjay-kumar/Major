#include "Task.h"
#include <cmath>
#include <stdexcept>
#include <limits>

Task::Task(int id, double posX, double posY, double deadline,
           double initialValue, double decayRate, double weight)
    : id(id), posX(posX), posY(posY), deadline(deadline),
      initialValue(initialValue), decayRate(decayRate),
      weight(weight), completed(false)
{
    if (id <= 0) {
        throw std::invalid_argument("Task ID must be positive");
    }
    if (deadline <= 0) {
        throw std::invalid_argument("Deadline must be positive");
    }
    if (initialValue <= 0) {
        throw std::invalid_argument("Initial value must be positive");
    }
    if (decayRate < 0 || decayRate > 1) {
        throw std::invalid_argument("Decay rate must be between 0 and 1");
    }
    if (weight < 0) {
        throw std::invalid_argument("Weight cannot be negative");
    }
}

// Getters
int Task::getId() const { return id; }
double Task::getPosX() const { return posX; }
double Task::getPosY() const { return posY; }
double Task::getDeadline() const { return deadline; }
double Task::getInitialValue() const { return initialValue; }
double Task::getDecayRate() const { return decayRate; }
double Task::getWeight() const { return weight; }

double Task::getCurrentValue(double currentTime) const {
    if (completed || currentTime >= deadline) {
        return 0.0;
    }
    return initialValue * ::exp(-decayRate * currentTime);
}

double Task::calculatePriority(double currentTime, double distance) const {
    const double epsilon = std::numeric_limits<double>::epsilon();
    double timeValue = getCurrentValue(currentTime);
    double distanceFactor = 1.0 / (1.0 + distance + epsilon);
    return timeValue * distanceFactor;
}

void Task::update(double timeStep) {
    // Future extension: update task state over time if needed
}

void Task::markCompleted() {
    completed = true;
}

bool Task::isCompleted() const {
    return completed;
}

double Task::distanceTo(double x, double y) const {
    return ::hypot(posX - x, posY - y);  // More numerically stable
}

double Task::getX() const {
    return posX;  // Return the X-coordinate
}

// Getter for Y-coordinate
double Task::getY() const {
    return posY;  // Return the Y-coordinate
}