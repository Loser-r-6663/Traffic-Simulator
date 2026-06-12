#ifndef VehicleFactory_h
#define VehicleFactory_h

#include "Vehicle.h"
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>

class VehicleFactory
{
    private:
    VehicleFactory() {}
    ~VehicleFactory() {}
    VehicleFactory(const VehicleFactory &) = delete;
    VehicleFactory &operator=(const VehicleFactory &) = delete;
    std::unordered_map<std::string, std::function<std::shared_ptr<Vehicle>(int)>> registryMap;

    public:
    static VehicleFactory &getInstance();
    void registerVehicle(const std::string &typeName, std::function<std::shared_ptr<Vehicle>(int)> creator);
    std::shared_ptr<Vehicle> createVehicle(const std::string &typeName, int id);
};


#endif /* VehicleFactory_h */