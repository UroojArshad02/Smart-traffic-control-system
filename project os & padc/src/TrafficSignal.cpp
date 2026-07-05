#include "../include/TrafficSignal.h"

TrafficSignal::TrafficSignal(float x, float y)
{
    state = SignalState::RED;
    timer = 5;

    redLight.setRadius(10.f);
    yellowLight.setRadius(10.f);
    greenLight.setRadius(10.f);

    redLight.setPosition(sf::Vector2f(x, y));
    yellowLight.setPosition(sf::Vector2f(x, y + 25.f));
    greenLight.setPosition(sf::Vector2f(x, y + 50.f));

    redLight.setFillColor(sf::Color(100, 0, 0));
    yellowLight.setFillColor(sf::Color(100, 100, 0));
    greenLight.setFillColor(sf::Color(0, 100, 0));
}

void TrafficSignal::setState(SignalState newState)
{
    state = newState;

    if (state == SignalState::RED) {
        redLight.setFillColor(sf::Color::Red);
        yellowLight.setFillColor(sf::Color(100, 100, 0));
        greenLight.setFillColor(sf::Color(0, 100, 0));
    }
    else if (state == SignalState::YELLOW) {
        redLight.setFillColor(sf::Color(100, 0, 0));
        yellowLight.setFillColor(sf::Color::Yellow);
        greenLight.setFillColor(sf::Color(0, 100, 0));
    }
    else {
        redLight.setFillColor(sf::Color(100, 0, 0));
        yellowLight.setFillColor(sf::Color(100, 100, 0));
        greenLight.setFillColor(sf::Color::Green);
    }
}

SignalState TrafficSignal::getState()
{
    return state;
}

void TrafficSignal::setTimer(int t)
{
    timer = t;
}

int TrafficSignal::getTimer()
{
    return timer;
}

void TrafficSignal::decreaseTimer()
{
    if (timer > 0) timer--;
}

void TrafficSignal::draw(sf::RenderWindow &window, sf::Font &font)
{
    window.draw(redLight);
    window.draw(yellowLight);
    window.draw(greenLight);

    // 🔥 TIMER TEXT
    sf::Text timerText(font, std::to_string(timer), 14);
    timerText.setFillColor(sf::Color::White);

    sf::Vector2f pos = redLight.getPosition();
    timerText.setPosition(sf::Vector2f(pos.x, pos.y - 20));

    window.draw(timerText);
}
