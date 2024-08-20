#include "Snake.hpp"

class Food {
private:
    sf::RectangleShape food;

public:
    Food();
    void placeFood(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    const sf::RectangleShape& getShape() const;

};