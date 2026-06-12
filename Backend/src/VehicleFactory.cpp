#include "../include/VehicleFactory.h"

VehicleFactory &VehicleFactory::getInstance()
{
    static VehicleFactory instance;
    if (instance.registryMap.empty())
    {
        instance.registerVehicle("Motorbike", [](int id) { return new Motorbike(id); });
        instance.registerVehicle("Car", [](int id) { return new Car(id); });
        instance.registerVehicle("Truck", [](int id) { return new Truck(id); });
    }
    return instance;
}

Vehicle *VehicleFactory::createVehicle(const std::string &typeName, int id)
{
    auto it = registryMap.find(typeName);
    if (it != registryMap.end())
    {
        return it->second(id);
    }
    return nullptr;
}

void VehicleFactory::registerVehicle(const std::string &typeName, std::function<Vehicle*(int)> creator)
{
    registryMap[typeName] = creator;
}