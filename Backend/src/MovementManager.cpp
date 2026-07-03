#include "../machine/MovementManager.h"
#include "../include/Vehicle.h"
#include <algorithm>
#include <cmath>
#include "../lib/VehicleTemplate.h"
#include "../include/Intersection.h"

#include "../include/Map.h"
#include "../machine/PathFindingMachine.h"

MovementManager::MovementManager() {}

MovementManager::~MovementManager() {}

MovementManager &MovementManager::getInstance()
{
    static MovementManager instance;
    return instance;
}

void MovementManager::addVehicle(std::shared_ptr<Vehicle> vehicle)
{
    vehicles.push_back(vehicle);
}

double MovementManager::distance(Vector2D pos1, Vector2D pos2)
{
    return std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));
}

void MovementManager::handleIntersectionArrival(Vehicle *vehicle)
{
    vehicle->setNextTargetIntersection();
    Intersection *nextTarget = vehicle->getTargetIntersection().get();

    if (nextTarget != nullptr)
    {
        Vector2D curPos = vehicle->getPosition();
        Vector2D nextPos = nextTarget->getPosition();

        Vector2D direction = nextPos - curPos;
        double dist = distance(curPos, nextPos);

        if (dist > 0.5f)
        {
            double maxSpeed = 0.0;
            for (const auto &tpl : VEHICLE_TEMPLATES)
            {
                if (tpl.typeId == vehicle->getTypeId())
                {
                    maxSpeed = tpl.maxSpeed;
                    break;
                }
            }

            Vector2D newVelocity = (direction / dist) * static_cast<float>(maxSpeed);
            vehicle->setVelocity(newVelocity);
        }
    }
    else
    {
        vehicle->setVelocity(Vector2D{0.0f, 0.0f});
    }
}

void MovementManager::normalMove(Vehicle *vehicle, float deltaTime)
{
    Vector2D curVelocity = vehicle->getVelocity();
    Vector2D curPosition = vehicle->getPosition();
    Vector2D newPos = curPosition + curVelocity * deltaTime;
    vehicle->setPosition(newPos);
}

void MovementManager::update(float deltaTime)
{
    const double EPSILON = 2;
    for (auto &vehiclePtr : vehicles)
    {
        Vehicle *vehicle = vehiclePtr.get();
        if (vehicle == nullptr || vehicle->isNeedDespawn())
            continue;

        if (!vehicle->hasRoute() && vehicle->getEndIntersection() != nullptr && vehicle->getTargetIntersection() != nullptr)
        {
            std::shared_ptr<Intersection> startNode = Map::getInstance().getIntersection(vehicle->getTargetIntersection()->getId());
            std::shared_ptr<Intersection> endNode = Map::getInstance().getIntersection(vehicle->getEndIntersection()->getId());

            if (startNode != nullptr && endNode != nullptr)
            {
                auto calculatedPath = PathfindingMachine::getInstance().findPath(startNode, endNode);

                vehicle->setRoute(calculatedPath);

                handleIntersectionArrival(vehicle);
            }
        }

        if (vehicle->getTargetIntersection() != nullptr)
        {
            Vector2D curPos = vehicle->getPosition();
            Vector2D targetPos = vehicle->getTargetIntersection()->getPosition();

            if (distance(curPos, targetPos) < EPSILON)
            {
                handleIntersectionArrival(vehicle);
            }

            normalMove(vehicle, deltaTime);
        }
        if (distance(vehicle->getPosition(), vehicle->getEndIntersection()->getPosition()) < EPSILON)
        {
            vehicle->setDespawn(true);
        }
    }
}

std::vector<std::shared_ptr<Vehicle>> &MovementManager::getVehicles()
{
    return vehicles;
}