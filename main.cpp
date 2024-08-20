#include "food.hpp"


void handleInput(Snake& snake, float speed) {
    sf::Vector2f currentDirection = snake.getDirection();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && currentDirection.y == 0.f) {
        snake.changeDirection(sf::Vector2f(0.f, -speed));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && currentDirection.y == 0.f) {
        snake.changeDirection(sf::Vector2f(0.f, speed));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && currentDirection.x == 0.f) {
        snake.changeDirection(sf::Vector2f(-speed, 0.f));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && currentDirection.x == 0.f) {
        snake.changeDirection(sf::Vector2f(speed, 0.f));
    }
}

void drawGameOverScreen(sf::RenderWindow& window, sf::Text& gameOverText, sf::Text& restartText) {
    window.draw(gameOverText);
    window.draw(restartText);
}

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Snake Game");
    srand(static_cast<unsigned>(time(0)));

    float speed;
    if (argc == 2) {
        std::string difficulty = argv[1];
        if (difficulty == "easy") speed = 200.f;
        else if (difficulty == "medium") speed = 300.f;
        else if (difficulty == "hard") speed = 400.f;
        else if (difficulty == "super-hard") speed = 500.f;
        else speed = 200.f;
    } else {
        speed = 200.f;
    }

    Snake snake(speed);
    Food food;
    food.placeFood(window);

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

    bool gameOver = false;
    int score = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
            if (gameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                snake.reset(speed);
                score = 0;
                gameOver = false;
                food.placeFood(window);
            }
        }

        if (!gameOver) {
            handleInput(snake, speed);

            sf::Time deltaTime = clock.restart();
            snake.move(deltaTime);

            if (snake.checkCollisionWithWall(window) || snake.checkSelfCollision()) {
                gameOver = true;
            }

            if (snake.checkCollisionWithFood(food.getShape())) {
                snake.increaseSpeed();
                std::cout << snake.getSpeed() <<std::endl;
                score++;
                snake.grow();
                food.placeFood(window);
            }
        }

        window.clear(sf::Color::Black);
        food.draw(window);
        scoreText.setString("Score: " + std::to_string(score));
        window.draw(scoreText);

        if (gameOver) {
            drawGameOverScreen(window, gameOverText, restartText);
        }

        snake.draw(window);
        window.display();
    }

    return 0;
}
