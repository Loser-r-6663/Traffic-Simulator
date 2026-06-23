#ifndef DESPAWNMANAGER_H
#define DESPAWNMANAGER_H

#include <vector>
#include <memory>

class Vehicle;

class DespawnManager
{
private:
    DespawnManager();
    ~DespawnManager();
    DespawnManager(const DespawnManager &) = delete;
    DespawnManager &operator=(const DespawnManager &) = delete;

public:
    static DespawnManager &getInstance();
    void process(std::vector<std::shared_ptr<Vehicle>> &vehicles);
};

#endif /*DESPAWNMANAGER_H*/