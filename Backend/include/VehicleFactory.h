#ifndef VehicleFactory_h
#define VehicleFactory_h

#include "Vehicle.h"
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>

class VehicleTemplate;

class VehicleFactory
{
private:
    VehicleFactory() {}
    ~VehicleFactory() {}
    VehicleFactory(const VehicleFactory &) = delete;
    VehicleFactory &operator=(const VehicleFactory &) = delete;
    std::unordered_map<std::string, std::function<std::shared_ptr<Vehicle>(int)>> registryMap;
    std::unordered_map<int, VehicleTemplate> registryTemplates;

public:
    static VehicleFactory &getInstance();

    std::unordered_map<int, VehicleTemplate> &getRegistryTemplates();

    void registerVehicle(const std::string &typeName, std::function<std::shared_ptr<Vehicle>(int)> creator);
    std::shared_ptr<Vehicle> createVehicle(const std::string &typeName, int id);
    void loadTemplatesFromFile(const std::string &filePath);
    void registerTemplate(const int &typeId, const VehicleTemplate &templateData);
};

#endif /* VehicleFactory_h */