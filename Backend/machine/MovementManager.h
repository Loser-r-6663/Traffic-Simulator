#ifndef MOVEMENTMANAGER_H
#define MOVEMENTMANAGER_H

#include <vector>
#include <memory>
#include "../lib/Vector2D.h"

class Vehicle;


class MovementManager
{
    private:
        MovementManager();
        ~MovementManager();
        MovementManager(const MovementManager &) = delete;
        MovementManager &operator=(const MovementManager &) = delete;
        std::vector<std::shared_ptr<Vehicle>> vehicles;
        void handleIntersectionArrival(Vehicle* vehicle);
        void normalMove(Vehicle* vehicle, float deltaTime);
        double distance(Vector2D pos1, Vector2D pos2);
    public:
        static MovementManager &getInstance();
        void addVehicle(std::shared_ptr<Vehicle> vehicle);
        void removeVehicle(std::shared_ptr<Vehicle> vehicle);
        void update(float deltaTime);

};

#endif /* MOVEMENTMANAGER_H */