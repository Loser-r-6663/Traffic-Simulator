#include "../include/Vehicle.h"
#include <iostream>

Vehicle::Vehicle() : id(0), typeId(0), posX(0.0), posY(0.0), curSpeed(0.0), direction(0.0), curAcceleration(0.0) {}
Vehicle::Vehicle(int id, int typeId) : id(id), typeId(typeId), posX(0.0), posY(0.0), curSpeed(0.0), direction(0.0), curAcceleration(0.0) {}
Vehicle::~Vehicle() {}

int Vehicle::getId() const { return id; }
int Vehicle::getTypeId() const { return typeId; }
double Vehicle::getPosX() const { return posX; }
double Vehicle::getPosY() const { return posY; }
double Vehicle::getCurSpeed() const { return curSpeed; }
double Vehicle::getDirection() const { return direction; }
double Vehicle::getCurAcceleration() const { return curAcceleration; }
void Vehicle::setPosition(double x, double y)
{
    posX = x;
    posY = y;
}
void Vehicle::setSpeed(double speed) { curSpeed = speed; }
void Vehicle::setDirection(double direction) { this->direction = direction; }
void Vehicle::setAcceleration(double acceleration) { curAcceleration = acceleration; }

Motorbike::Motorbike() : Vehicle() {}
Motorbike::Motorbike(int id) : Vehicle(id, 1) {}
Motorbike::~Motorbike() {}
void Motorbike::info()
{
    std::cout << "Motorbike ID: " << getId() << ", Position: (" << getPosX() << ", " << getPosY() << "), Speed: " << getCurSpeed() << " m/s, Direction: " << getDirection() << " degrees, Acceleration: " << getCurAcceleration() << " m/s^2" << std::endl;
}

Car::Car() : Vehicle() {}
Car::Car(int id) : Vehicle(id, 2) {}
Car::~Car() {}
void Car::info()
{
    std::cout << "Car ID: " << getId() << ", Position: (" << getPosX() << ", " << getPosY() << "), Speed: " << getCurSpeed() << " m/s, Direction: " << getDirection() << " degrees, Acceleration: " << getCurAcceleration() << " m/s^2" << std::endl;
}

Truck::Truck() : Vehicle() {}
Truck::Truck(int id) : Vehicle(id, 3) {}
Truck::~Truck() {}
void Truck::info()
{
    std::cout << "Truck ID: " << getId() << ", Position: (" << getPosX() << ", " << getPosY() << "), Speed: " << getCurSpeed() << " m/s, Direction: " << getDirection() << " degrees, Acceleration: " << getCurAcceleration() << " m/s^2" << std::endl;
}
