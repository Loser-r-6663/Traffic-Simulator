#ifndef Vehicle_h
#define Vehicle_h

#include <string>
#include <memory>
#include "../lib/Vector2D.h"
#include <vector>

class Intersection;


class Vehicle
{
private:
    int id;
    int typeId;
    Vector2D position;
    Vector2D velocity;
    Intersection* targetIntersection;
    Intersection* endIntersection;
    std::vector<Intersection*> route;
    size_t currentRouteIndex;
    double curAcceleration;
    bool needDespawn = false;

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
    Intersection* getTargetIntersection() const;
    Intersection* getEndIntersection() const;


    void setNextTargetIntersection();
    void setTargetIntersection(Intersection* intersection);
    void setEndIntersection(Intersection* intersection);
    void setRoute(const std::vector<std::shared_ptr<Intersection>>& route);
    void setPosition(const Vector2D &pos);
    void setVelocity(const Vector2D &vel);
    void setAcceleration(double acceleration);
    void setDespawn(bool isDespawn);

    bool hasRoute() const;
    bool isNeedDespawn() const;
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
{
public:
    Car();
    Car(int id);
    ~Car() override;
    void info() override;
};
class Truck : public Vehicle
{
public:
    Truck();
    Truck(int id);
    ~Truck() override;
    void info() override;
};

#endif /* Vehicle_h */