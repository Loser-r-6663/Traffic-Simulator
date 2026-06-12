#ifndef Vehicle_h
#define Vehicle_h

#include <string>
#include <memory>
#include "../lib/Vector2D.h"

class Vehicle
{
private:
    int id;
    int typeId;
    Vector2D position;
    Vector2D velocity;
    double curAcceleration;

public:
    Vehicle();
    Vehicle(int id, int typeId);
    virtual ~Vehicle();
    virtual void info() = 0;

    int getId() const;
    int getTypeId() const;
    Vector2D getPosition() const;
    Vector2D getVelocity() const;
    double getCurAcceleration() const;

    void setPosition(const Vector2D &pos);
    void setVelocity(const Vector2D &vel);
    void setAcceleration(double acceleration);
};

class Motorbike : public Vehicle
{
public:
    Motorbike();
    Motorbike(int id);
    ~Motorbike() override;
    void info() override;
};
class Car : public Vehicle
{public:
    Car();
    Car(int id);
    ~Car() override;
    void info() override {}
};
class Truck : public Vehicle
{public:
    Truck();
    Truck(int id);
    ~Truck() override;
    void info() override {}
};

#endif /* Vehicle_h */