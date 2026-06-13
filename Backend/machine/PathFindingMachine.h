#ifndef PATHFINDINGMACHINE_H
#define PATHFINDINGMACHINE_H

#include <vector>
#include <memory>

class Intersection;

class PathfindingMachine
{
private:
    PathfindingMachine();
    ~PathfindingMachine();
    PathfindingMachine(const PathfindingMachine &) = delete;
    PathfindingMachine &operator=(const PathfindingMachine &) = delete;

public:
    static PathfindingMachine &getInstance();

    std::vector<std::shared_ptr<Intersection>> findPath(
        std::shared_ptr<Intersection> start,
        std::shared_ptr<Intersection> end);
};

#endif /* PATHFINDINGMACHINE_H */