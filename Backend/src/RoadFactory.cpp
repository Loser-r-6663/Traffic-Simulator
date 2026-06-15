#include "../include/RoadFactory.h"
#include "../include/Lane.h"
#include "../lib/RoadTemplate.h"
#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>

using json = nlohmann::json;

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

void RoadFactory::registerTemplate(const int &typeId, const RoadTemplate &templateData)
{
    registryTemplates.insert_or_assign(templateData.typeName, templateData);
}

void RoadFactory::loadTemplatesFromFile(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Khong the mo file: " << filePath << std::endl;
        return;
    }

    json data;
    file >> data;

    for (const auto &item : data["roads"])
    {
        std::string typeName = item["typeName"];
        int typeId = item["typeId"];
        int numLanes = item["numLanes"];
        double maxSpeed = item["maxSpeed"];

        RoadTemplate templateData(typeName, typeId, numLanes, maxSpeed);
        registerTemplate(typeId, templateData);
    }
}