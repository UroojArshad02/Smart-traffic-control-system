#include "../include/Vehicle.h"

Vehicle::Vehicle(float x, float y, int dir)
{
    direction = dir;

    speed = 3.5f;  

    shape.setSize(sf::Vector2f(20.f, 10.f));
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(sf::Vector2f(x, y));
}

sf::Vector2f Vehicle::getPosition() {
    return shape.getPosition();
}

int Vehicle::getDirection() {
    return direction;
}

void Vehicle::update(std::vector<TrafficSignal>& signals)
{
    sf::Vector2f pos = shape.getPosition();

    float stopY_top = 300;
    float stopY_bottom = 420;
    float stopX_left = 420;
    float stopX_right = 580;

    if (direction == 0 && pos.y <= stopY_bottom && signals[2].getState() != SignalState::GREEN)
        return;

    if (direction == 1 && pos.x >= stopX_left && signals[3].getState() != SignalState::GREEN)
        return;

    if (direction == 2 && pos.y >= stopY_top && signals[0].getState() != SignalState::GREEN)
        return;

    if (direction == 3 && pos.x <= stopX_right && signals[1].getState() != SignalState::GREEN)
        return;

    if (direction == 0) shape.move(sf::Vector2f(0, -speed));
    if (direction == 1) shape.move(sf::Vector2f(speed, 0));
    if (direction == 2) shape.move(sf::Vector2f(0, speed));
    if (direction == 3) shape.move(sf::Vector2f(-speed, 0));
}

void Vehicle::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}
