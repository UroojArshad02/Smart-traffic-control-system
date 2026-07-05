#ifndef VEHICLE_H
#define VEHICLE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "TrafficSignal.h"

class Vehicle {
private:
    sf::RectangleShape shape;
    float speed;
    int direction;

public:
    Vehicle(float x, float y, int dir);

    void update(std::vector<TrafficSignal>& signals);
    void draw(sf::RenderWindow &window);

    sf::Vector2f getPosition();
    int getDirection();   // 🔥 NEW
};

#endif
