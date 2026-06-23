#include "../machine/DespawnManager.h"
#include "../include/Vehicle.h"
#include <iostream>
DespawnManager::DespawnManager() {}

DespawnManager::~DespawnManager() {}

DespawnManager &DespawnManager::getInstance()
{
    static DespawnManager instance;
    return instance;
}

void DespawnManager::process(std::vector<std::shared_ptr<Vehicle>> &vehicles)
{
    auto it = vehicles.begin();
    while (it != vehicles.end())
    {
        if ((*it)->isNeedDespawn())
        {
            std::cout << "[Despawn] Da huy xe [Id]:" << (*it)->getId() << std::endl;
            it = vehicles.erase(it);
        }
        else
            ++it;
    }
}
