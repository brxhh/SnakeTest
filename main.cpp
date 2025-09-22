#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>
#include <SFML/System.hpp>
using namespace std;

sf::Vector2i direction(1, 0);
sf::Clock gameClock;
const int width = 40;
const int height = 20;
const int blockSize = 16;
int x = width / 2 - 1;
int y = height / 2 - 1;
int fruitX = rand() % width;
int fruitY = rand() % height;
int fruitsEaten = 0;
int score = 0;
float moveDelay = 0.12f;
const float minDelay = 0.05f;
vector<sf::Vector2i> snake;

void Setup() {
    snake.clear();
    x = width / 2 - 1;
    y = height / 2 - 1;
    snake.push_back(sf::Vector2i(x, y));
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw(sf::RenderWindow &window) {
    window.clear(sf::Color::Black);

    for (const auto& block : snake) {
        sf::RectangleShape snakeBlock(sf::Vector2f(blockSize, blockSize));
        snakeBlock.setFillColor(sf::Color::Green);
        snakeBlock.setPosition(sf::Vector2f(block.x * blockSize, block.y * blockSize));
        window.draw(snakeBlock);
    }

    sf::RectangleShape fruit(sf::Vector2f(blockSize, blockSize));
    fruit.setFillColor(sf::Color::Red);
    fruit.setPosition(sf::Vector2f(fruitX * blockSize, fruitY * blockSize));
    window.draw(fruit);

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

    if (x == fruitX && y == fruitY) {
        score++;
        fruitsEaten++;
        fruitX = rand() % width;
        fruitY = rand() % height;

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