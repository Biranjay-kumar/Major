#ifndef UAV_H
#define UAV_H

#include <string>  // For std::string in getStatus()

class Task; // Forward declaration

class UAV {
public:
    // Constructor
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
    int getId() const { return id; }
    double getWeightCapacity() const { return weightCapacity; }
    double getEnergyCapacity() const { return energyCapacity; }
    double getCurrentEnergy() const { return currentEnergy; }
    double getPosX() const { return posX; }
    double getPosY() const { return posY; }
    
    // Task management
    void assignTask(const Task& task);
    void completeCurrentTask();
    
    // Additional methods from implementation
    void emergencyLand();
    std::string getStatus() const;

private:
    // Validation helpers
    void validateConstructionParameters() const;
    void validateCoordinates(double x, double y) const;

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