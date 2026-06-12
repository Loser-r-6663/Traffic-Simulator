#include "../include/Vehicle.h"

Vehicle::Vehicle() : id(0), typeId(0), posX(0.0), posY(0.0), curSpeed(0.0), direction(0.0), curAcceleration(0.0) {}
Vehicle::Vehicle(int id, int typeId) : id(id), typeId(typeId), posX(0.0), posY(0.0), curSpeed(0.0), direction(0.0), curAcceleration(0.0) {}

int Vehicle::getId() const { return id; }
int Vehicle::getTypeId() const { return typeId; }
double Vehicle::getPosX() const { return posX; }
double Vehicle::getPosY() const { return posY; }
double Vehicle::getCurSpeed() const { return curSpeed; }
double Vehicle::getDirection() const { return direction; }
double Vehicle::getCurAcceleration() const { return curAcceleration; }
void Vehicle::setPosition(double x, double y) { posX = x; posY = y; }
void Vehicle::setSpeed(double speed) { curSpeed = speed; }
void Vehicle::setDirection(double direction) { this->direction = direction; }
void Vehicle::setAcceleration(double acceleration) { curAcceleration = acceleration; }
Vehicle::~Vehicle() {}