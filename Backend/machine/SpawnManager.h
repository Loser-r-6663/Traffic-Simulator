#ifndef SPAWNMANAGER_H
#define SPAWNMANAGER_H

#include <vector>
#include <string>
#include <memory>

class Intersection;
class Vehicle;

class SpawnManager
{
private:
    SpawnManager();
    ~SpawnManager();
    SpawnManager(const SpawnManager &) = delete;
    SpawnManager &operator=(const SpawnManager &) = delete;

    bool autoSpawnEnabled;
    float spawnTimer;
    float spawnInterval;

    int currentVehicleId;

public:
    static SpawnManager &getInstance();

    void initialize(float interval = 3.0f, bool enableAuto = false);

    std::shared_ptr<Vehicle> spawnVehicle(const std::string &vehicleType,
                                          Intersection *startIntersection,
                                          Intersection *endIntersection);

    void update(float deltaTime);

    void setAutoSpawn(bool enable) { autoSpawnEnabled = enable; }
    void setSpawnInterval(float interval) { spawnInterval = interval; }
};

#endif /* SPAWNMANAGER_H */