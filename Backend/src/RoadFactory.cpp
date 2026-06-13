#include "../include/RoadFactory.h"
#include "../include/Lane.h"
#include "../lib/RoadTemplate.h"

RoadFactory &RoadFactory::getInstance()
{
    static RoadFactory instance;
    return instance;
}

std::shared_ptr<Road> RoadFactory::createRoad(const std::string &typeName, int id, Vector2D position, 
                                             std::shared_ptr<Intersection> startInter, 
                                             std::shared_ptr<Intersection> endInter)
{
    auto road = std::make_shared<Road>(id, position, startInter, endInter);
    
    for (const auto& tmpl : ROAD_TEMPLATES) {
        if (tmpl.typeName == typeName) {
            for (int i = 0; i < tmpl.numLanes; ++i) {
                int laneId = id * 10 + (i + 1);
                auto lane = std::make_shared<Lane>(laneId, position);
                lane->setMaxSpeed(tmpl.maxSpeed);
                road->addLane(lane);
            }
            break;
        }
    }
    
    return road;
}