#include "food.hpp"

Food::Food() {
    food.setSize(sf::Vector2f(20.f, 20.f));
    food.setFillColor(sf::Color::Red);
}

void Food::placeFood(sf::RenderWindow& window) {
    int x = rand() % (window.getSize().x / 20) * 20;
    int y = rand() % (window.getSize().y / 20) * 20;
    food.setPosition(static_cast<float>(x), static_cast<float>(y));
}

void Food::draw(sf::RenderWindow& window) {
    window.draw(food);
}

const sf::RectangleShape& Food::getShape() const {
    return food;
}