#ifndef TASK_H
#define TASK_H

class Task {
public:
    // Constructor
    Task(int id, double posX, double posY, double deadline, 
         double initialValue, double decayRate);
    
    // Getters
    int getId() const;
    double getPosX() const;
    double getPosY() const;
    double getDeadline() const;
    double getCurrentValue(double currentTime) const;
    double getInitialValue() const;
    double getDecayRate() const;
    
    // Calculate priority score (can be customized)
    double calculatePriority(double currentTime, double distance) const;
    
    // Update task state
    void update(double timeStep);

    // **New methods**
    /// Mark this task as completed
    void markCompleted();
    
    /// Check if the task has been completed
    bool isCompleted() const;
    
    /// Compute Euclidean distance to point (x, y)
    double distanceTo(double x, double y) const;

		double getWeight() const;

private:
    int id;
    double posX, posY;
    double deadline;
    double initialValue;
    double decayRate;
    bool completed;
		double weight;
};

#endif // TASK_H
