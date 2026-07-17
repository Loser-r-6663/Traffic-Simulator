#include "../machine/RoadFactory.h"
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

std::shared_ptr<Road> RoadFactory::createRoad(int typeId, int id, Vector2D position, 
                                             std::shared_ptr<Intersection> startInter, 
                                             std::shared_ptr<Intersection> endInter)
{
    auto road = std::make_shared<Road>(id, position, startInter, endInter);

    RoadTemplate templateData("", 0, 1, 0.0);
    bool foundTemplate = false;

    auto it = registryTemplates.find(typeId);
    if (it != registryTemplates.end())
    {
        templateData = it->second;
        foundTemplate = true;
    }
    else
    {
        for (const auto& tmpl : ROAD_TEMPLATES)
        {
            if (tmpl.typeId == typeId)
            {
                templateData = tmpl;
                foundTemplate = true;
                break;
            }
        }
    }

    if (!foundTemplate)
    {
        std::cerr << "[RoadFactory] Khong tim thay template cho road typeId=" << typeId << ". Su dung mac dinh.\n";
        templateData = ROAD_TEMPLATES[0];
    }

    for (int i = 0; i < templateData.numLanes; ++i) {
        int laneId = id * 10 + (i + 1);
        auto lane = std::make_shared<Lane>(laneId, position);
        lane->setMaxSpeed(templateData.maxSpeed);
        road->addLane(lane);
    }
    
    return road;
}

void RoadFactory::registerTemplate(int typeId, const RoadTemplate &templateData)
{
    registryTemplates.insert_or_assign(typeId, templateData);
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

    for (const auto &item : data["road_templates"])
    {
        std::string typeName = item["typeName"];
        int typeId = item["typeId"];
        int numLanes = item["numLanes"];
        double maxSpeed = item["maxSpeed"];

        RoadTemplate templateData(typeName, typeId, numLanes, maxSpeed);
        registerTemplate(typeId, templateData);
    }
}