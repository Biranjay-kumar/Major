#include "Task.h"
#include <cmath>
#include <stdexcept>

Task::Task(int id, double posX, double posY, double deadline,
           double initialValue, double decayRate)
    : id(id), posX(posX), posY(posY), deadline(deadline),
      initialValue(initialValue), decayRate(decayRate), completed(false) {
    
    if (deadline <= 0) {
        throw std::invalid_argument("Deadline must be positive");
    }
    if (initialValue <= 0) {
        throw std::invalid_argument("Initial value must be positive");
    }
    if (decayRate < 0 || decayRate > 1) {
        throw std::invalid_argument("Decay rate must be between 0 and 1");
    }
}

// Getter implementations
int Task::getId() const { return id; }
double Task::getPosX() const { return posX; }
double Task::getPosY() const { return posY; }
double Task::getDeadline() const { return deadline; }
double Task::getInitialValue() const { return initialValue; }
double Task::getDecayRate() const { return decayRate; }

double Task::getCurrentValue(double currentTime) const {
    if (completed || currentTime >= deadline) {
        return 0.0;
    }
		// Instead of std::exp(...)
double value = ::exp(-decayRate * currentTime);
    return initialValue * value;
}

double Task::calculatePriority(double currentTime, double distance) const {
    double timeValue = getCurrentValue(currentTime);
    double distanceFactor = 1.0 / (1.0 + distance);
    return timeValue * distanceFactor;
}

void Task::update(double timeStep) {
    // Future extension: update task state over time if needed.
}

// **New method implementations**

void Task::markCompleted() {
    completed = true;
}

bool Task::isCompleted() const {
    return completed;
}

double Task::distanceTo(double x, double y) const {
    double dx = posX - x;
    double dy = posY - y;
		double value = ::sqrt(dx * dx + dy * dy);
    return value;
}

double Task::getWeight() const {
	return weight;
}

