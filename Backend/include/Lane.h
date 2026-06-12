#ifndef LANE_H
#define LANE_H

#include <vector>
#include <memory>
#include "../lib/Vector2D.h"

class Vehicle;

class Lane
{
    private:
        int id;
        Vector2D position;
        double maxSpeed;
    public:
        std::vector<std::shared_ptr<Vehicle>> Vehicles;

        Lane(int id, Vector2D position);
        ~Lane();
        
        int getId();
        Vector2D getPosition();
        double getMaxSpeed();
        void setMaxSpeed(double speed);
        void addVehicle(std::shared_ptr<Vehicle> vehicle);
};

#endif /* LANE_H */