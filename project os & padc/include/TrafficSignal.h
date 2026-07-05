#ifndef TRAFFICSIGNAL_H
#define TRAFFICSIGNAL_H

#include <SFML/Graphics.hpp>

enum class SignalState {
    RED,
    YELLOW,
    GREEN
};

class TrafficSignal {
private:
    SignalState state;

    sf::CircleShape redLight;
    sf::CircleShape yellowLight;
    sf::CircleShape greenLight;

    int timer; // 🔥 NEW

public:
    TrafficSignal(float x, float y);

    void draw(sf::RenderWindow &window, sf::Font &font); // updated
    void setState(SignalState newState);

    SignalState getState();

    void setTimer(int t); // 🔥 NEW
    int getTimer();       // 🔥 NEW
    void decreaseTimer(); // 🔥 NEW
};

#endif
