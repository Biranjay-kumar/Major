#ifndef UAV_H
#define UAV_H

class Task; // Forward declaration

class UAV {
public:
    UAV(int id, double weightCapacity, double energyCapacity, 
        double posX, double posY);
    
    // Core functionality
    double distanceTo(double x, double y) const;
    void updateEnergy(double energyCost);
    void refuel();
    void setPosition(double x, double y);
    
    // Status checks
    bool canCarry(double weight) const;
    bool canReach(double x, double y, double returnEnergy = 0) const;
    bool needsRefuel(double threshold) const;
    
    // Getters
    int getId() const;
    double getWeightCapacity() const;
    double getEnergyCapacity() const;
    double getCurrentEnergy() const;
    double getPosX() const;
    double getPosY() const;
    
    // Task management
    void assignTask(const Task& task);
    void completeCurrentTask();
    
private:
    const int id;
    const double weightCapacity;
    const double energyCapacity;
    double currentEnergy;
    double posX, posY;
    
    // Task tracking
    bool hasTask;
    double currentTaskWeight;
};

#endif // UAV_H