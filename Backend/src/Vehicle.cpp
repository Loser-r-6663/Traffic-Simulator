#include "../include/Vehicle.h"
#include <iostream>
#include <cmath>
Vehicle::Vehicle() : id(0), typeId(0), position(0.0, 0.0), velocity(0.0, 0.0), curAcceleration(0.0) {}
Vehicle::Vehicle(int id, int typeId) : id(id), typeId(typeId), position(0.0, 0.0), velocity(0.0, 0.0), curAcceleration(0.0) {}
Vehicle::~Vehicle() {}

int Vehicle::getId() const { return id; }
int Vehicle::getTypeId() const { return typeId; }
Vector2D Vehicle::getPosition() const { return position; }
Vector2D Vehicle::getVelocity() const { return velocity; }
double Vehicle::getCurAcceleration() const { return curAcceleration; }
void Vehicle::setPosition(const Vector2D &pos) { position = pos; }
void Vehicle::setVelocity(const Vector2D &vel) { velocity = vel; }
void Vehicle::setAcceleration(double acceleration) { curAcceleration = acceleration; }

Motorbike::Motorbike() : Vehicle() {}
Motorbike::Motorbike(int id) : Vehicle(id, 1) {}
Motorbike::~Motorbike() {}
void Motorbike::info()
{
    double speedMagnitude = std::sqrt(getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y);

    std::cout << "[Motorbike ID: " << getId() << "]\n"
              << " - Position    : (" << getPosition().x << ", " << getPosition().y << ")\n"
              << " - Velocity Vector: (" << getVelocity().x << ", " << getVelocity().y << ")\n"
              << " - Current Speed  : " << speedMagnitude << " m/s\n"
              << " - Acceleration   : " << getCurAcceleration() << " m/s^2\n";
}

Car::Car() : Vehicle() {}
Car::Car(int id) : Vehicle(id, 2) {}
Car::~Car() {}
void Car::info()
{
    double speedMagnitude = std::sqrt(getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y);

    std::cout << "[Car ID: " << getId() << "]\n"
              << " - Position    : (" << getPosition().x << ", " << getPosition().y << ")\n"
              << " - Velocity Vector: (" << getVelocity().x << ", " << getVelocity().y << ")\n"
              << " - Current Speed  : " << speedMagnitude << " m/s\n"
              << " - Acceleration   : " << getCurAcceleration() << " m/s^2\n";
}

Truck::Truck() : Vehicle() {}
Truck::Truck(int id) : Vehicle(id, 3) {}
Truck::~Truck() {}
void Truck::info()
{
    double speedMagnitude = std::sqrt(getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y);

    std::cout << "[Truck ID: " << getId() << "]\n"
              << " - Position    : (" << getPosition().x << ", " << getPosition().y << ")\n"
              << " - Velocity Vector: (" << getVelocity().x << ", " << getVelocity().y << ")\n"
              << " - Current Speed  : " << speedMagnitude << " m/s\n"
              << " - Acceleration   : " << getCurAcceleration() << " m/s^2\n";
}
