#include "../include/IntersectionFactory.h"

IntersectionFactory &IntersectionFactory::getInstance()
{
    static IntersectionFactory instance;
    return instance;
}

std::shared_ptr<Intersection> IntersectionFactory::createIntersection(int id, Vector2D position)
{
    auto intersection = std::make_shared<Intersection>(id, position);
    return intersection;
}