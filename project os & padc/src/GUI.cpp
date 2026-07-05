#include "../include/GUI.h"
#include <algorithm>

GUI::GUI()
    : window(sf::VideoMode(sf::Vector2u(1000, 800)), "Smart Traffic System")
{
    signals.emplace_back(480, 200);
    signals.emplace_back(700, 380);
    signals.emplace_back(480, 550);
    signals.emplace_back(250, 380);

    signals[0].setState(SignalState::GREEN);
    signals[0].setTimer(5);

    running = true;
    logicThread = std::thread(&GUI::logicLoop, this);
}

GUI::~GUI()
{
    running = false;
    if (logicThread.joinable())
        logicThread.join();
}

void GUI::logicLoop()
{
    int spawnTimer = 0;
    static int timerTick = 0;

    while (running) {

        std::this_thread::sleep_for(std::chrono::milliseconds(5));

        std::lock_guard<std::mutex> lock(mtx);

        // ⏱️ TIMER UPDATE
        timerTick++;
        if (timerTick % 60 == 0) {

            for (auto &s : signals)
                s.decreaseTimer();

            for (int i = 0; i < 4; i++) {
                if (signals[i].getTimer() == 0 && signals[i].getState() == SignalState::GREEN) {

                    int next = (i + 1) % 4;

                    signals[i].setState(SignalState::RED);
                    signals[i].setTimer(5);

                    signals[next].setState(SignalState::GREEN);
                    signals[next].setTimer(5);
                }
            }
        }

        // 🚗 SPAWN
        spawnTimer++;
        if (spawnTimer % 120 == 0) {
            int dir = rand() % 4;

            if (dir == 0) vehicles.emplace_back(500, 800, 0);
            if (dir == 1) vehicles.emplace_back(0, 380, 1);
            if (dir == 2) vehicles.emplace_back(500, 0, 2);
            if (dir == 3) vehicles.emplace_back(1000, 380, 3);
        }

        for (auto &v : vehicles)
            v.update(signals);

        vehicles.erase(
            std::remove_if(vehicles.begin(), vehicles.end(),
                [](Vehicle &v) {
                    auto pos = v.getPosition();
                    return (pos.x < -50 || pos.x > 1050 || pos.y < -50 || pos.y > 850);
                }),
            vehicles.end()
        );
    }
}

void GUI::run()
{
    sf::Font font;
    if (!font.openFromFile("assets/arial.ttf")) return;

    // 📊 COUNTERS
    sf::Text northText(font, "", 16);
    sf::Text eastText(font, "", 16);
    sf::Text southText(font, "", 16);
    sf::Text westText(font, "", 16);

    northText.setPosition({850, 100});
    eastText.setPosition({850, 150});
    southText.setPosition({850, 200});
    westText.setPosition({850, 250});

    while (window.isOpen()) {

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        std::lock_guard<std::mutex> lock(mtx);

        // 📊 UPDATE COUNTERS
        int count[4] = {0};
        for (auto &v : vehicles)
            count[v.getDirection()]++;

        northText.setString("North: " + std::to_string(count[0]));
        eastText.setString("East: " + std::to_string(count[1]));
        southText.setString("South: " + std::to_string(count[2]));
        westText.setString("West: " + std::to_string(count[3]));

        window.clear(sf::Color(30, 30, 30));

        sf::RectangleShape v(sf::Vector2f(120.f, 800.f));
        v.setPosition({440.f, 0.f});

        sf::RectangleShape h(sf::Vector2f(1000.f, 120.f));
        h.setPosition({0.f, 340.f});

        v.setFillColor(sf::Color(100,100,100));
        h.setFillColor(sf::Color(100,100,100));

        window.draw(v);
        window.draw(h);

        for (auto &s : signals)
            s.draw(window, font);

        for (auto &vcl : vehicles)
            vcl.draw(window);

        window.draw(northText);
        window.draw(eastText);
        window.draw(southText);
        window.draw(westText);

        window.display();
    }
}
