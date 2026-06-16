#include "../machine/SimulationManager.h"
#include "../machine/MovementManager.h"
#include "../machine/SpawnManager.h"
#include <thread>
#include <iostream>

SimulationManager::SimulationManager() : isRunning(false) {}

SimulationManager::~SimulationManager() {}

SimulationManager &SimulationManager::getInstance()
{
    static SimulationManager instance;
    return instance;
}

void SimulationManager::initialize()
{
    isRunning = false;
    std::cout << "[SimulationManager] He thong da san sang.\n";
}

void SimulationManager::start()
{
    if (isRunning) return;
    
    isRunning = true;
    std::cout << "[SimulationManager] Bat dau vong lap mo phong...\n";

    lastFrameTime = std::chrono::steady_clock::now();

    while (isRunning)
    {
        auto currentFrameTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = currentFrameTime - lastFrameTime;
        float deltaTime = elapsed.count();
        
        lastFrameTime = currentFrameTime;

        if (deltaTime > 0.1f) deltaTime = 0.1f; 

        MovementManager::getInstance().update(deltaTime);

        SpawnManager::getInstance().update(deltaTime);
        // DataLayer::getInstance().writeCache();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void SimulationManager::pause()
{
    isRunning = false; 
    std::cout << "[SimulationManager] Da tam dung mo phong.\n";
}

void SimulationManager::stop()
{
    isRunning = false;
    std::cout << "[SimulationManager] Dung mo phong va lam sach du lieu.\n";
    // Có thể giải phóng danh sách xe tại đây
}