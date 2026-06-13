#ifndef MAP_H
#define MAP_H

#include <vector>
#include <memory>
#include <unordered_map>

class Intersection;
class Road;

class Map
{
private:
    Map();
    ~Map();
    Map(const Map &) = delete;
    Map &operator=(const Map &) = delete;

    std::vector<std::shared_ptr<Intersection>> intersections;
    std::vector<std::shared_ptr<Road>> roads;
    std::unordered_map<int, std::shared_ptr<Intersection>> intersectionLookup;

public:
    static Map &getInstance();

    void addIntersection(std::shared_ptr<Intersection> intersection);
    void addRoad(std::shared_ptr<Road> road);

    const std::vector<std::shared_ptr<Intersection>>& getAllIntersections() const;
    const std::vector<std::shared_ptr<Road>>& getAllRoads() const;

    std::shared_ptr<Intersection> getRandomIntersection() const;

    std::shared_ptr<Intersection> getIntersection(int id) const;

    void clear();
};

#endif /* MAP_H */