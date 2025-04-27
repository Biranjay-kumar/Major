#ifndef TASK_H
#define TASK_H

#include <stdexcept>
#include <string>

class Task {
public:
    // Constructor
    Task(int id, double posX, double posY, double deadline,
         double initialValue, double decayRate, double weight = 0.0);
    
    // Getters
    int getId() const;
    double getPosX() const;
    double getPosY() const;
    double getDeadline() const;
    double getInitialValue() const;
    double getDecayRate() const;
    double getWeight() const;
    
    // Task value calculations
    double getCurrentValue(double currentTime) const;
    double calculatePriority(double currentTime, double distance) const;
    
    // Task management
    void markCompleted();
    bool isCompleted() const;
    void update(double timeStep);
    
    // Distance calculation
    double distanceTo(double x, double y) const;
    double getX() const;  // Getter for X-coordinate
    double getY() const;  // Getter for Y-coordinate

private:
    int id;
    double posX;
    double posY;
    double deadline;
    double initialValue;
    double decayRate;
    double weight;
    bool completed;
};

#endif // TASK_H
