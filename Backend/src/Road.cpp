#include "../include/Road.h"
#include "../include/Lane.h"


Road::Road(int id, Vector2D position, std::shared_ptr<Intersection> startIntersections, std::shared_ptr<Intersection> endIntersections)
    : id(id), position(position), startIntersections(startIntersections), endIntersections(endIntersections) {}
Road::~Road() {}

int Road::getId() { return id; }
Vector2D Road::getPosition() { return position; }

void Road::addLane(std::shared_ptr<Lane> lane)
{
    lanes.push_back(lane);
}