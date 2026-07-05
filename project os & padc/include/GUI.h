#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include <mutex>
#include <semaphore>

#include "TrafficSignal.h"
#include "Vehicle.h"

class GUI {
private:
    sf::RenderWindow window;

    std::vector<TrafficSignal> signals;
    std::vector<Vehicle> vehicles;

    std::thread logicThread;
    std::mutex mtx;
    bool running;

    // 🔥 SEMAPHORES
    std::binary_semaphore north{0};
    std::binary_semaphore east{0};
    std::binary_semaphore south{0};
    std::binary_semaphore west{0};

public:
    GUI();

    void run();
    void logicLoop();

    ~GUI();
};

#endif
