#ifndef ROAD_FACTORY_H
#define ROAD_FACTORY_H

#include "Road.h"
#include "../lib/RoadTemplate.h"
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

    std::unordered_map<int, RoadTemplate> registryTemplates;

public:
    static RoadFactory &getInstance();
    void registerTemplate(int typeId, const RoadTemplate &templateData);
    std::shared_ptr<Road> createRoad(int typeId, int id, Vector2D position, 
                                     std::shared_ptr<Intersection> startInter, 
                                     std::shared_ptr<Intersection> endInter);

    void loadTemplatesFromFile(const std::string &filePath);
};

#endif /* ROAD_FACTORY_H */