#ifndef INTERSECTION_FACTORY_H
#define INTERSECTION_FACTORY_H

#include "Intersection.h"
#include <unordered_map>
#include <string>
#include <memory>

class IntersectionFactory
{
private:
    IntersectionFactory() {}
    ~IntersectionFactory() {}
    IntersectionFactory(const IntersectionFactory &) = delete;
    IntersectionFactory &operator=(const IntersectionFactory &) = delete;


public:
    static IntersectionFactory &getInstance();
    std::shared_ptr<Intersection> createIntersection(int id, Vector2D position);
};

#endif /* INTERSECTION_FACTORY_H */