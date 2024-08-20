#include "Snake.hpp"

Snake::Snake(float initSpeed) {
    speed = initSpeed;
    direction = sf::Vector2f(speed, 0.f);
    sf::RectangleShape segment(sf::Vector2f(20.f, 20.f));
    segment.setFillColor(sf::Color::Green);
    segment.setPosition(400.f, 300.f);
    segments.push_back(segment);
}

void Snake::reset(float initSpeed) {
    segments.clear();
    speed = initSpeed;
    direction = sf::Vector2f(speed, 0.f);
    sf::RectangleShape segment(sf::Vector2f(20.f, 20.f));
    segment.setFillColor(sf::Color::Green);
    segment.setPosition(400.f, 300.f);
    segments.push_back(segment);
}

void Snake::move(sf::Time deltaTime) {
    sf::Vector2f newHeadPosition = segments[0].getPosition() + direction * deltaTime.asSeconds();
    for (int i = segments.size() - 1; i > 0; --i) {
        segments[i].setPosition(segments[i - 1].getPosition());
    }
    segments[0].setPosition(newHeadPosition);
}

void Snake::grow() {
    for (int i = 0; i < 20; ++i) {
        sf::RectangleShape newSegment(sf::Vector2f(20.f, 20.f));
        newSegment.setFillColor(sf::Color::Green);
        newSegment.setPosition(segments.back().getPosition());
        segments.push_back(newSegment);
    }
}

void Snake::changeDirection(const sf::Vector2f& newDirection) {
    direction = newDirection;
}

bool Snake::checkCollisionWithWall(const sf::RenderWindow& window) {
    sf::FloatRect headBounds = segments[0].getGlobalBounds();
    return headBounds.left < 0 || headBounds.top < 0 ||
           headBounds.left + headBounds.width > window.getSize().x ||
           headBounds.top + headBounds.height > window.getSize().y;
}

bool Snake::checkSelfCollision() {
    sf::FloatRect headBounds = segments[0].getGlobalBounds();

    if (segments.size() > 200) {
        for (int i = 200; i < segments.size();i++){
            if (headBounds.intersects(segments[i].getGlobalBounds()))
                return true;
        }
    }
    return false;
}

bool Snake::checkCollisionWithFood(const sf::RectangleShape& food) {
    return segments[0].getGlobalBounds().intersects(food.getGlobalBounds());
}

void Snake::draw(sf::RenderWindow& window) {
    for (auto& segment : segments) {
        window.draw(segment);
    }
}

float Snake::getSpeed() const {
    return speed;
}

void Snake::increaseSpeed() {
    speed += (speed / 20);
}

int Snake::getSize() const {
    return segments.size();
}

sf::Vector2f Snake::getDirection() const {
    return direction;
}