#ifndef ROAD_H
#define ROAD_H

#include <vector>
#include <memory>
#include "../lib/Vector2D.h"



class Intersection;
class Lane;

class Road
{
private:
    int id;
    Vector2D position;

public:
    std::shared_ptr<Intersection> startIntersections;
    std::shared_ptr<Intersection> endIntersections;
    std::vector<std::shared_ptr<Lane>> lanes;

    Road(int id, Vector2D position, std::shared_ptr<Intersection> startIntersections, std::shared_ptr<Intersection> endIntersections);
    ~Road();

    int getId();
    Vector2D getPosition();
    void addLane(std::shared_ptr<Lane> lane);
};

#endif /* ROAD_H */