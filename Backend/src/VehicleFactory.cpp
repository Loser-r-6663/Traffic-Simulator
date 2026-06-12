#include "../include/VehicleFactory.h"

VehicleFactory &VehicleFactory::getInstance()
{
    static VehicleFactory instance;
    if (instance.registryMap.empty())
    {
        instance.registerVehicle("Motorbike", [](int id) { return std::make_shared<Motorbike>(id); });
        instance.registerVehicle("Car", [](int id) { return std::make_shared<Car>(id); });
        instance.registerVehicle("Truck", [](int id) { return std::make_shared<Truck>(id); });
    }
    return instance;
}

std::shared_ptr<Vehicle> VehicleFactory::createVehicle(const std::string &typeName, int id)
{
    auto it = registryMap.find(typeName);
    if (it != registryMap.end())
    {
        return it->second(id);
    }
    return nullptr;
}

void VehicleFactory::registerVehicle(const std::string &typeName, std::function<std::shared_ptr<Vehicle>(int)> creator)
{
    registryMap[typeName] = creator;
}