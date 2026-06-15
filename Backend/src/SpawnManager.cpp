#include "../machine/SpawnManager.h"
#include "../machine/MovementManager.h"
#include "../include/VehicleFactory.h"
#include "../include/Intersection.h"
#include "../include/Vehicle.h"
#include "../include/Map.h"
#include "../lib/VehicleTemplate.h"


#include <random>
#include <iostream>

SpawnManager::SpawnManager()
    : autoSpawnEnabled(false), spawnTimer(0.0f), spawnInterval(3.0f), currentVehicleId(1)
{
}

SpawnManager::~SpawnManager() {}

SpawnManager &SpawnManager::getInstance()
{
    static SpawnManager instance;
    return instance;
}

void SpawnManager::initialize(float interval, bool enableAuto)
{
    spawnInterval = interval;
    autoSpawnEnabled = enableAuto;
    spawnTimer = 0.0f;
    std::cout << "[SpawnManager] Khoi tao thanh cong (Interval: " << spawnInterval << "s, Auto: " << (autoSpawnEnabled ? "ON" : "OFF") << ").\n";
}

std::shared_ptr<Vehicle> SpawnManager::spawnVehicle(const std::string &vehicleType,
                                                    Intersection *startIntersection,
                                                    Intersection *endIntersection)
{
    if (startIntersection == nullptr || endIntersection == nullptr)
    {
        std::cerr << "[SpawnManager] Loi: Diem xuat phat hoac diem dich bi NULL!\n";
        return nullptr;
    }

    int newId = currentVehicleId++;
    std::shared_ptr<Vehicle> newVehicle = VehicleFactory::getInstance().createVehicle(vehicleType, newId);

    if (newVehicle == nullptr)
    {
        std::cerr << "[SpawnManager] Loi: Khong the tao loai xe: " << vehicleType << "\n";
        return nullptr;
    }

    newVehicle->setPosition(startIntersection->getPosition());

    newVehicle->setTargetIntersection(startIntersection);
    newVehicle->setEndIntersection(endIntersection);

    MovementManager::getInstance().addVehicle(newVehicle);

    std::cout << "[SpawnManager] Sinh xe thanh cong: " << vehicleType
              << " [ID: " << newVehicle->getId()
              << "] | Xuat phat: " << startIntersection->getId()
              << " -> Dich: " << endIntersection->getId() << "\n";

    return newVehicle;
}
void SpawnManager::update(float deltaTime)
{
    if (!autoSpawnEnabled)
        return;

    spawnTimer += deltaTime;

    if (spawnTimer >= spawnInterval)
    {
        spawnTimer -= spawnInterval;

        std::shared_ptr<Intersection> start = Map::getInstance().getRandomIntersection();
        std::shared_ptr<Intersection> end = Map::getInstance().getRandomIntersection();

        while (start != nullptr && end != nullptr && start->getId() == end->getId())
        {
            end = Map::getInstance().getRandomIntersection();
        }

        if (start != nullptr && end != nullptr)
        {
            auto &templates = VehicleFactory::getInstance().getRegistryTemplates();
            std::vector<std::string> typeNames;
            typeNames.reserve(templates.size());
            for (const auto &entry : templates)
            {
                typeNames.push_back(entry.second.typeName);
            }

            if (!typeNames.empty())
            {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<size_t> dis(0, typeNames.size() - 1);
                size_t randomIndex = dis(gen);
                std::string randomType = typeNames[randomIndex];
                spawnVehicle(randomType, start.get(), end.get());
            }
        }
    }
}