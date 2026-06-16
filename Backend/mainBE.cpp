#include <iostream>
#include <winsock2.h>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <nlohmann/json.hpp>
#include "machine/MapLoader.h"
#include "machine/SimulationManager.h"
#include "machine/SpawnManager.h"
#include "machine/MovementManager.h"
#include "include/VehicleFactory.h"
#include "include/RoadFactory.h"
#include "include/Map.h"

SOCKET clientSocket;
SOCKET serverSocket;

using json = nlohmann::json;

int initServer()
{
    WSADATA wsaData;
    int check = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (check != 0)
    {
        std::cout << "Khoi tao Winsock that bai! Ma loi: " << check << "" << std::endl;
        return 1;
    }
    std::cout << "Khoi tao Winsock thanh cong!" << std::endl;

    // tao socket, tao cong
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET)
    {
        std::cout << "Tao Socket that bai! Ma loi: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 2;
    }
    std::cout << "Tao Socket thanh cong!" << std::endl;

    // khai bao cong
    sockaddr_in serverHint;
    serverHint.sin_family = AF_INET;
    serverHint.sin_port = htons(8080);
    serverHint.sin_addr.S_un.S_addr = INADDR_ANY;

    // gan cong
    int bindResult = bind(serverSocket, (sockaddr *)&serverHint, sizeof(serverHint));
    if (bindResult == SOCKET_ERROR)
    {
        std::cout << "Gan cong (Bind) that bai! Ma loi: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 3;
    }
    std::cout << "Gan cong (Bind) thanh cong!" << std::endl;

    // mo cong, cho phep ket noi
    int listenResult = listen(serverSocket, SOMAXCONN);
    if (listenResult == SOCKET_ERROR)
    {
        std::cout << "Khong the lang nghe! Ma loi: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 4;
    }
    std::cout << "Lang nghe thanh cong!" << std::endl;
    sockaddr_in clientHint;
    int clientSize = sizeof(clientHint);
    // tao socket rieng cho client
    clientSocket = accept(serverSocket, (sockaddr *)&clientHint, &clientSize);
    if (clientSocket == INVALID_SOCKET)
    {
        std::cout << "Accept client that bai! Ma loi: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 5;
    }

    std::cout << "Client da ket noi." << std::endl;
    return 0;
}

#pragma pack(push, 1)
struct vehiclePacked
{
    int typeId;
    float x;
    float y;
};
#pragma pack(pop)

int main()
{
    int initResult = initServer();
    if (initResult != 0)
        return initResult;

    std::cout << "[MAIN] Accept thanh cong, bat dau load du lieu..." << std::endl;
    std::cout.flush();

    const std::string mapPath = "data/map_config.json";
    const std::string templatePath = "data/templates.json";

    Map::getInstance().clear();

    std::cout << "[MAIN] Dang load map tu " << mapPath << std::endl;
    std::cout.flush();
    if (!MapLoader::loadMap(mapPath))
    {
        std::cerr << "Khong the tai ban do tu: " << mapPath << std::endl;
        return 6;
    }
    std::cout << "[MAIN] Load map thanh cong" << std::endl;
    std::cout.flush();

    std::cout << "[MAIN] Dang load templates..." << std::endl;
    std::cout.flush();
    VehicleFactory::getInstance().loadTemplatesFromFile(templatePath);
    RoadFactory::getInstance().loadTemplatesFromFile(templatePath);
    std::cout << "[MAIN] Load templates thanh cong" << std::endl;
    std::cout.flush();

    std::cout << "[MAIN] Dang khoi tao SpawnManager..." << std::endl;
    std::cout.flush();
    SpawnManager::getInstance().initialize(3.0f, true);
    std::cout << "[MAIN] SpawnManager khoi tao xong" << std::endl;
    std::cout.flush();

    std::cout << "[MAIN] Dang spawn xe dau tien..." << std::endl;
    std::cout.flush();
    auto startIntersection = Map::getInstance().getIntersection(1);
    auto endIntersection = Map::getInstance().getIntersection(3);
    if (startIntersection && endIntersection)
    {
        SpawnManager::getInstance().spawnVehicle("Car", startIntersection.get(), endIntersection.get());
    }
    std::cout << "[MAIN] Spawn xe thanh cong" << std::endl;
    std::cout.flush();

    std::chrono::time_point<std::chrono::steady_clock> lastFrameTime = std::chrono::steady_clock::now();

    bool isRunning = true;
    while (isRunning)
    {
        char buffer[1024];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0)
        {
            std::cout << "Client ngat ket noi";
            break;
        }
        auto currentFrameTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = currentFrameTime - lastFrameTime;
        float deltaTime = elapsed.count();

        lastFrameTime = currentFrameTime;

        if (deltaTime > 0.1f)
            deltaTime = 0.1f;

        MovementManager::getInstance().update(deltaTime);

        std::vector<vehiclePacked> packedVehicles;
        int cnt = 0;
        std::vector<std::shared_ptr<Vehicle>> vehicles = MovementManager::getInstance().getVehicles();
        for (auto const &vehicle : vehicles)
        {
            vehiclePacked packedVehicle;
            packedVehicle.typeId = vehicle->getTypeId();
            packedVehicle.x = vehicle->getPosition().x;
            packedVehicle.y = vehicle->getPosition().y;
            packedVehicles.push_back(packedVehicle);
            cnt++;
        }

        int packedVehiclesSize = cnt * sizeof(vehiclePacked);
        // header
        send(clientSocket, (char *)&packedVehiclesSize, sizeof(packedVehiclesSize), 0);
        // number
        send(clientSocket, (char *)&cnt, sizeof(cnt), 0);
        // data
        send(clientSocket, (char *)packedVehicles.data(), packedVehiclesSize, 0);
        packedVehicles.clear();
        auto startIntersection = Map::getInstance().getRandomIntersection();
        auto endIntersection = Map::getInstance().getRandomIntersection();
        if (startIntersection && endIntersection)
        {
            SpawnManager::getInstance().spawnVehicle("Car", startIntersection.get(), endIntersection.get());
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}