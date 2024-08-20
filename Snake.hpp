#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cstdlib> 
#include <ctime>   

class Snake {
private:
    std::vector<sf::RectangleShape> segments;
    sf::Vector2f direction;
    float speed;

public:
    Snake(float initSpeed);
    void reset(float initSpeed);
    void move(sf::Time deltaTime);
    void grow();
    void changeDirection(const sf::Vector2f& newDirection);
    bool checkCollisionWithWall(const sf::RenderWindow& window);
    bool checkSelfCollision();
    bool checkCollisionWithFood(const sf::RectangleShape& food);
    void draw(sf::RenderWindow& window);
    float getSpeed() const;
    void increaseSpeed();
    int getSize() const;
    sf::Vector2f getDirection() const;

};