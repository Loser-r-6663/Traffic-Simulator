#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include <memory>
#include "../lib/Vector2D.h"

class Road;
class Intersection
{
private:
    int id;
    Vector2D position;

public:
    std::vector<std::shared_ptr<Road>> incomingRoads;
    std::vector<std::shared_ptr<Road>> outgoingRoads;

    Intersection(int id, Vector2D position);
    ~Intersection();

    void addIncomingRoad(std::shared_ptr<Road> road);
    void addOutgoingRoad(std::shared_ptr<Road> road);
    int getId();
    Vector2D getPosition();
    std::vector<std::shared_ptr<Road>> getIncomingRoads();
    std::vector<std::shared_ptr<Road>> getOutgoingRoads();
};

#endif /* INTERSECTION_H */