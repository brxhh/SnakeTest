#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>
#include <SFML/System.hpp>
using namespace std;

constexpr int width = 40, height = 20, blockSize = 16;
int x = width/2-1, y = height/2-1;
int score = 0, fruitsEaten = 0;
float moveDelay = 0.12f, minDelay = 0.05f;
sf::Vector2i direction(1,0);
sf::Clock gameClock;
vector<sf::Vector2i> snake;
sf::Vector2i fruit(rand()%width, rand()%height);

void Setup() {
    snake = {{x,y}};
    direction = {1,0};
    fruit = {rand()%width, rand()%height};
    score = fruitsEaten = 0;
    moveDelay = 0.12f;
}

void Draw(sf::RenderWindow &window) {
    window.clear(sf::Color::Black);

    for (const auto& block : snake) {
        sf::RectangleShape snakeBlock(sf::Vector2f(blockSize, blockSize));
        snakeBlock.setFillColor(sf::Color::Green);
        snakeBlock.setPosition(sf::Vector2f(block.x * blockSize, block.y * blockSize));
        window.draw(snakeBlock);
    }

    sf::RectangleShape fruitShape(sf::Vector2f(blockSize, blockSize));
    fruitShape.setFillColor(sf::Color::Red);
    fruitShape.setPosition(sf::Vector2f(fruit.x * blockSize, fruit.y * blockSize));
    window.draw(fruitShape);

    window.display();
}

void Input(sf::RenderWindow &window) {
    while (true) {
        auto eventOpt = window.pollEvent();
        if (!eventOpt.has_value())
            break;
        const sf::Event &event = *eventOpt;

        if (event.is<sf::Event::Closed>()) {
            window.close();
        }
        else if (const auto *keyPressed = event.getIf<sf::Event::KeyPressed>()) {
            auto key = keyPressed->scancode;
            using Sc = sf::Keyboard::Scancode;

            if (key == Sc::Up && direction.y != 1)
                direction = sf::Vector2i(0, -1);
            else if (key == Sc::Down && direction.y != -1)
                direction = sf::Vector2i(0, 1);
            else if (key == Sc::Left && direction.x != 1)
                direction = sf::Vector2i(-1, 0);
            else if (key == Sc::Right && direction.x != -1)
                direction = sf::Vector2i(1, 0);

            //Key (keyCode):
            /*
            auto keyCode = keyPressed->key;
            if (keyCode == Key::Up && direction.y != 1)
                direction = sf::Vector2i(0, -1);
            else if (keyCode == Key::Down && direction.y != -1)
                direction = sf::Vector2i(0, 1);
            else if (keyCode == Key::Left && direction.x != 1)
                direction = sf::Vector2i(-1, 0);
            else if (keyCode == Key::Right && direction.x != -1)
                direction = sf::Vector2i(1, 0);
            */
        }
    }
}

void Logic(sf::RenderWindow &window) {
    if (gameClock.getElapsedTime().asSeconds() < moveDelay)
        return;
    gameClock.restart();

    x += direction.x;
    y += direction.y;

    if (x < 0 || x >= width || y < 0 || y >= height) {
        window.close();
        return;
    }

    sf::Vector2i newHead(x, y);
    snake.insert(snake.begin(), newHead);

    for (size_t i = 1; i < snake.size(); i++) {
        if (snake[i] == newHead) {
            window.close();
            return;
        }
    }

    if (x == fruit.x && y == fruit.y) {
        score++;
        fruitsEaten++;
        fruit = {rand() % width, rand() % height};

        if (fruitsEaten % 3 == 0 && moveDelay > minDelay) {
            moveDelay -= 0.005f;
        }
    } else {
        snake.pop_back();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(width * blockSize, height * blockSize)), "Snake Game");
    window.setFramerateLimit(10);
    Setup();
    while (window.isOpen()) {
        Input(window);
        Logic(window);
        Draw(window);
    }

    return 0;
}