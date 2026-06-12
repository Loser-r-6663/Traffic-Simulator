#ifndef Vehicle_h
#define Vehicle_h

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

class Vehicle
{
private:
    int id;
    int typeId;
    double posX;
    double posY;
    double curSpeed;
    double direction;
    double curAcceleration;

public:
    Vehicle();
    Vehicle(int id, int typeId);
    virtual ~Vehicle();
    virtual void info() = 0;

    int getId() const;
    int getTypeId() const;
    double getPosX() const;
    double getPosY() const;
    double getCurSpeed() const;
    double getDirection() const;
    double getCurAcceleration() const;
    void setPosition(double x, double y);
    void setSpeed(double speed);
    void setDirection(double direction);
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