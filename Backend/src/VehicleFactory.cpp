#include "../machine/VehicleFactory.h"
#include "../include/Vehicle.h"
#include "../lib/VehicleTemplate.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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

std::unordered_map<int, VehicleTemplate> &VehicleFactory::getRegistryTemplates()
{
    return registryTemplates;
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

void VehicleFactory::loadTemplatesFromFile(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Khong the mo file: " << filePath << std::endl;
        return;
    }

    json data;
    file >> data;
    for (const auto &item : data["vehicle_templates"])
    {
        std::string typeName = item["typeName"];
        int typeId = item["typeId"];
        double maxSpeed = item["maxSpeed"];
        double lenght = item["length"];
        double width = item["width"];
        double acceleration = item["acceleration"];
        double deceleration = item.value("deceleration", 0.0);

        VehicleTemplate templateData(typeName, typeId, lenght, width, maxSpeed, acceleration);
        registerTemplate(typeId, templateData);
    }
}

void VehicleFactory::registerTemplate(const int &typeId, const VehicleTemplate &templateData)
{
    registryTemplates.insert_or_assign(templateData.typeId, templateData);
}