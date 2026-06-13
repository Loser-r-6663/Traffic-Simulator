#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include <chrono>

class SimulationManager
{
private:
    SimulationManager();
    ~SimulationManager();
    SimulationManager(const SimulationManager &) = delete;
    SimulationManager &operator=(const SimulationManager &) = delete;

    bool isRunning;
    
    std::chrono::time_point<std::chrono::steady_clock> lastFrameTime;

public:
    static SimulationManager &getInstance();

    void initialize();

    void start();

    void pause();
    void stop();

    bool getIsRunning() const { return isRunning; }
};

#endif /* SIMULATIONMANAGER_H */