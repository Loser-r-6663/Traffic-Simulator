#include "../include/Intersection.h"
#include "../include/Road.h"

Intersection::Intersection(int id, Vector2D position) : id(id), position(position) {}
Intersection::~Intersection() {}

void Intersection::addIncomingRoad(std::shared_ptr<Road> road)
{
    incomingRoads.push_back(road);
}
void Intersection::addOutgoingRoad(std::shared_ptr<Road> road)
{
    outgoingRoads.push_back(road);
}
int Intersection::getId() { return id; }
Vector2D Intersection::getPosition()
{
    return position;
}
std::vector<std::shared_ptr<Road>> Intersection::getIncomingRoads()
{
    return incomingRoads;
}
std::vector<std::shared_ptr<Road>> Intersection::getOutgoingRoads()
{
    return outgoingRoads;
}