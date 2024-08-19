#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cstdlib> 
#include <ctime>   

int main(int argc, char **argv) {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Snake Game");
    std::vector<sf::RectangleShape> snake;
        sf::RectangleShape segment(sf::Vector2f(20.f, 20.f));
        segment.setFillColor(sf::Color::Green);
        segment.setPosition(400.f, 300.f);
        snake.push_back(segment);
    float speed;
    if (argc == 2)
    {
        if (std::string(argv[1]) == "easy")
            speed = 200.f;
        else if (std::string(argv[1]) == "medium")
            speed = 300.f;
        else if (std::string(argv[1]) == "hard")
            speed = 400.f;
        else if (std::string(argv[1]) == "super-hard")
            speed = 500.f;
    }
    else
        speed = 200.f;
    sf::Vector2f direction(speed, 0.f);
    sf::Clock clock;
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) { 
        std::cerr << "Error loading font" << std::endl;
        return -1;
    }
    sf::Text gameOverText("Game Over", font, 200);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(1920 / 2 - gameOverText.getGlobalBounds().width / 2,
                             1080 / 2 - gameOverText.getGlobalBounds().height / 2);
    sf::Text scoreText("Score: 0", font, 100);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);
    sf::Text restartText("If you want to restart on the same difficulty Press: R", font, 50);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(1920 / 2 - restartText.getGlobalBounds().width / 2,
                            1080 / 2 + gameOverText.getGlobalBounds().height / 2 + 20);
    sf::RectangleShape food(sf::Vector2f(20.f, 20.f));
    food.setFillColor(sf::Color::Red);
    srand(static_cast<unsigned>(time(0)));
    auto placeFood = [&]() {
        int x = rand() % (window.getSize().x / 20) * 20;
        int y = rand() % (window.getSize().y / 20) * 20;
        food.setPosition(static_cast<float>(x), static_cast<float>(y));
    };
    placeFood();
    bool gameOver = false;
    int score = 0;
        auto resetGame = [&]() {
        snake.clear();
        sf::RectangleShape segment(sf::Vector2f(20.f, 20.f));
        segment.setFillColor(sf::Color::Green);
        segment.setPosition(400.f, 300.f);
        snake.push_back(segment);
        
        if (argc == 2) {
            if (std::string(argv[1]) == "easy")
                speed = 100.f;
            else if (std::string(argv[1]) == "medium")
                speed = 200.f;
            else if (std::string(argv[1]) == "hard")
                speed = 300.f;
            else if (std::string(argv[1]) == "super-hard")
                speed = 500.f;
        } else {
            speed = 200.f;
        }

        direction = sf::Vector2f(speed, 0.f);
        score = 0;
        gameOver = false;
        placeFood();
    };
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            if (event.type == sf::Event::Closed)
                window.close();
            if (gameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                resetGame();
            }
        }
        if (!gameOver) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && direction.y == 0)
                direction = sf::Vector2f(0.f, -speed);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && direction.y == 0)
                direction = sf::Vector2f(0.f, speed);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && direction.x == 0)
                direction = sf::Vector2f(-speed, 0.f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && direction.x == 0)
                direction = sf::Vector2f(speed, 0.f);
        }
        sf::Time deltaTime = clock.restart();
        if (!gameOver) {
        sf::Vector2f newHeadPosition = snake[0].getPosition() + direction * deltaTime.asSeconds();
        for (size_t i = snake.size() - 1; i > 0; --i) {
            snake[i].setPosition(snake[i - 1].getPosition());
        }
        snake[0].setPosition(newHeadPosition);
            sf::FloatRect headBounds = snake[0].getGlobalBounds();
            if (headBounds.left < 0 || headBounds.top < 0 ||
                headBounds.left + headBounds.width > window.getSize().x ||
                headBounds.top + headBounds.height > window.getSize().y) {
                gameOver = true;
            }
            if (headBounds.intersects(food.getGlobalBounds())) {
                speed += (speed / 20);
                ++score;
                for (int i = 0; i < 20; ++i) {
                    sf::RectangleShape newSegment(sf::Vector2f(20.f, 20.f));
                    newSegment.setFillColor(sf::Color::Green);
                    newSegment.setPosition(snake.back().getPosition());
                    snake.push_back(newSegment);
                }
                placeFood();
            }
            if (snake.size() > 200) {
                for (size_t i = 200; i < snake.size(); ++i) {
                    if (headBounds.intersects(snake[i].getGlobalBounds())) {
                        gameOver = true;
                        break;
                    }
                }
            }   

        }
        window.clear(sf::Color::Black);
        window.draw(food);
        scoreText.setString("Score: " + std::to_string(score));
        window.draw(scoreText);
        if (gameOver) {
            window.draw(gameOverText);
            window.draw(restartText);
        }
        for (size_t i = 0; i < snake.size(); ++i) {
            window.draw(snake[i]);
        }  
        window.display();
    }
    return 0;
}
