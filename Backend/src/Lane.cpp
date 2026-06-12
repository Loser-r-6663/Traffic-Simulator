#include "../include/Lane.h"
#include "../include/Vehicle.h"

Lane::Lane(int id, Vector2D position) : id(id), position(position), maxSpeed(0.0) {}
Lane::~Lane() {}

int Lane::getId() { return id; }
Vector2D Lane::getPosition() { return position; }
double Lane::getMaxSpeed() { return maxSpeed; }
void Lane::setMaxSpeed(double speed) { maxSpeed = speed; }
void Lane::addVehicle(std::shared_ptr<Vehicle> vehicle)
{
    Vehicles.push_back(vehicle);
}