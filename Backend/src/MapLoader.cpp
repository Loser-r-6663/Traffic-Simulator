#include "../machine/MapLoader.h"
#include "../include/Map.h"
#include "../include/Intersection.h"
#include "../include/Road.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool MapLoader::loadMap(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Khong the mo file: " << filePath << std::endl;
        return false;
    }

    json data;
    file >> data;

    // Nạp Intersections
    for (const auto &item : data["intersections"])
    {
        auto inter = std::make_shared<Intersection>(
            item["id"].get<int>(),
            Vector2D{item["x"].get<float>(), item["y"].get<float>()});
        Map::getInstance().addIntersection(inter);
    }

    // Nạp Roads
    for (const auto &item : data["roads"])
    {
        auto start = Map::getInstance().getIntersection(item["start_node"]);
        auto end = Map::getInstance().getIntersection(item["end_node"]);

        if (start && end)
        {
            // Khởi tạo Road với Intersection thay vì Vector2D nếu cần thiết
            auto road = std::make_shared<Road>(item["id"], Vector2D{0, 0}, start, end);
            Map::getInstance().addRoad(road);
        }
    }
    
    file.close();

    std::cout << "Load map hoan tat tu: " << filePath << std::endl;
    return true;
}