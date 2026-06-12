#ifndef ROAD_FACTORY_H
#define ROAD_FACTORY_H

#include "Road.h"
#include <unordered_map>
#include <string>
#include <memory>

class RoadFactory
{
private:
    RoadFactory() {}
    ~RoadFactory() {}
    RoadFactory(const RoadFactory &) = delete;
    RoadFactory &operator=(const RoadFactory &) = delete;

public:
    static RoadFactory &getInstance();
        
    std::shared_ptr<Road> createRoad(const std::string &typeName, int id, Vector2D position, 
                                     std::shared_ptr<Intersection> startInter, 
                                     std::shared_ptr<Intersection> endInter);
};

#endif /* ROAD_FACTORY_H */