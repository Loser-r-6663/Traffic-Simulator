#ifndef VEHICLETEMPLATE_H
#define VEHICLETEMPLATE_H

#include <string>

struct VehicleTemplate
{
    std::string typeName;
    int typeId;
    double length;
    double width;
    double maxSpeed;
    double acceleration;
    VehicleTemplate(const std::string &typeName, const int typeId, double length, double width, double maxSpeed, double acceleration)
        : typeName(typeName), typeId(typeId), length(length), width(width), maxSpeed(maxSpeed), acceleration(acceleration) {}
};

inline const VehicleTemplate VEHICLE_TEMPLATES[] = {
    VehicleTemplate("Motorbike", 1, 2.0, 0.8, 40.0, 3.0),
    VehicleTemplate("Car", 2, 4.5, 1.8, 60.0, 2.0),
    VehicleTemplate("Truck", 3, 6.0, 2.5, 30.0, 0.8)};



#endif /* VEHICLETEMPLATE_H */