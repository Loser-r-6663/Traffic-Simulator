#ifndef ROADTEMPLATE_H
#define ROADTEMPLATE_H

#include <vector>
#include <string>

struct RoadTemplate
{
    std::string typeName;
    int typeId;
    int numLanes;
    double maxSpeed;

    RoadTemplate(const std::string &name, int id, int numLanes, double maxSpeed)
        : typeName(name), typeId(id), numLanes(numLanes), maxSpeed(maxSpeed) {}
};

inline const RoadTemplate ROAD_TEMPLATES[] = {
    RoadTemplate("UrbanStreet", 1, 2, 50.0),
    RoadTemplate("Highway", 2, 3, 120.0),
    RoadTemplate("Alley", 3, 1, 20.0)};

#endif /* ROADTEMPLATE_H */