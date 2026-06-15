#include "../include/Map.h"
#include "../include/Intersection.h"
#include "../include/Road.h"
#include <random>

Map::Map() {}
Map::~Map() {}

Map &Map::getInstance()
{
    static Map instance;
    return instance;
}

void Map::addIntersection(std::shared_ptr<Intersection> intersection)
{
    intersections.push_back(intersection);
    intersectionLookup[intersection->getId()] = intersection;
}
void Map::addRoad(std::shared_ptr<Road> road)
{
    roads.push_back(road);
    if (road->startIntersections && road->endIntersections)
    {
        road->startIntersections->outgoingRoads.push_back(road);
        road->endIntersections->incomingRoads.push_back(road);
    }
}

const std::vector<std::shared_ptr<Intersection>> &Map::getAllIntersections() const
{
    return intersections;
}
const std::vector<std::shared_ptr<Road>> &Map::getAllRoads() const
{
    return roads;
}

std::shared_ptr<Intersection> Map::getRandomIntersection() const
{
    if (intersections.empty())
    {
        return nullptr;
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(0, intersections.size() - 1);

    return intersections[dis(gen)];
}

std::shared_ptr<Intersection> Map::getIntersection(int id) const
{
    auto it = intersectionLookup.find(id);
    if (it != intersectionLookup.end())
    {
        return it->second;
    }
    return nullptr;
}

void Map::clear()
{
    for (auto &intersection : intersections)
    {
        if (intersection)
        {
            intersection->incomingRoads.clear();
            intersection->outgoingRoads.clear();
        }
    }
    intersections.clear();
    roads.clear();
}