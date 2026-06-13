#include "../machine/PathFindingMachine.h"
#include "../include/Intersection.h"
#include "../include/Road.h"
#include "../lib/Vector2D.h"
#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <iostream>

struct NodeCost {
    std::shared_ptr<Intersection> intersection;
    double cost;

    bool operator>(const NodeCost& other) const {
        return cost > other.cost;
    }
};

PathfindingMachine::PathfindingMachine() {}
PathfindingMachine::~PathfindingMachine() {}

PathfindingMachine &PathfindingMachine::getInstance()
{
    static PathfindingMachine instance;
    return instance;
}

double calculateDistance(Vector2D p1, Vector2D p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}

std::vector<std::shared_ptr<Intersection>> PathfindingMachine::findPath(
    std::shared_ptr<Intersection> start, 
    std::shared_ptr<Intersection> end)
{
    std::vector<std::shared_ptr<Intersection>> emptyRoute;

    if (start == nullptr || end == nullptr) {
        std::cerr << "[PathfindingMachine] Loi: Diem xuat phat hoac diem dich bi NULL!\n";
        return emptyRoute;
    }

    if (start->getId() == end->getId()) {
        return { start };
    }

    std::unordered_map<int, double> gScore; // Lưu khoảng cách ngắn nhất đến từng nút giao
    std::unordered_map<int, std::shared_ptr<Intersection>> parentMap; // Bảng vết truy ngược đường đi
    std::priority_queue<NodeCost, std::vector<NodeCost>, std::greater<NodeCost>> openSet;

    gScore[start->getId()] = 0.0;
    openSet.push({ start, 0.0 });

    bool found = false;

    while (!openSet.empty()) {
        std::shared_ptr<Intersection> current = openSet.top().intersection;
        double currentCost = openSet.top().cost;
        openSet.pop();

        if (current->getId() == end->getId()) {
            found = true;
            break;
        }

        if (currentCost > gScore[current->getId()]) {
            continue;
        }

        for (const auto& road : current->getOutgoingRoads()) {
            if (road == nullptr) continue;

            std::shared_ptr<Intersection> neighbor = road->endIntersections;
            if (neighbor == nullptr) continue;

            double edgeWeight = calculateDistance(current->getPosition(), neighbor->getPosition());
            double tentativeGScore = currentCost + edgeWeight;

            if (gScore.find(neighbor->getId()) == gScore.end() || tentativeGScore < gScore[neighbor->getId()]) {
                gScore[neighbor->getId()] = tentativeGScore;
                parentMap[neighbor->getId()] = current; 
                openSet.push({ neighbor, tentativeGScore });
            }
        }
    }

    if (!found) {
        std::cout << "[PathfindingMachine] Canh bao: Khong tim thay duong di tu Nut " 
                  << start->getId() << " den Nut " << end->getId() << "\n";
        return emptyRoute;
    }

    std::vector<std::shared_ptr<Intersection>> totalPath;
    std::shared_ptr<Intersection> currTrace = end;

    while (currTrace->getId() != start->getId()) {
        totalPath.push_back(currTrace);
        currTrace = parentMap[currTrace->getId()];
    }
    totalPath.push_back(start);

    std::reverse(totalPath.begin(), totalPath.end());

    std::cout << "[PathfindingMachine] Tim duong ngan nhat thanh cong! (So chang: " << totalPath.size() << ")\n";
    return totalPath;
}