#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>

using namespace std;

const int width = 40;
const int height = 20;
const int blockSize = 16;
int x = width / 2 - 1;
int y = height / 2 - 1;
int fruitX = rand() % width;
int fruitY = rand() % height;
int score = 0;
sf::Vector2i direction(1, 0);
vector<sf::Vector2i> snake; // Vector to store snake blocks

void Setup(sf::RenderWindow &window) {
    window.setFramerateLimit(10);
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

    // Draw the snake
    for (const auto& block : snake) {
        sf::RectangleShape snakeBlock(sf::Vector2f(blockSize, blockSize));
        snakeBlock.setFillColor(sf::Color::Green);
        snakeBlock.setPosition(block.x * blockSize, block.y * blockSize);
        window.draw(snakeBlock);
    }

    // Draw the fruit
    sf::RectangleShape fruit(sf::Vector2f(blockSize, blockSize));
    fruit.setFillColor(sf::Color::Red);
    fruit.setPosition(fruitX * blockSize, fruitY * blockSize);
    window.draw(fruit);

    window.display();
}

void Input(sf::RenderWindow &window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up && direction.y != 1)
                direction = sf::Vector2i(0, -1);
            else if (event.key.code == sf::Keyboard::Down && direction.y != -1)
                direction = sf::Vector2i(0, 1);
            else if (event.key.code == sf::Keyboard::Left && direction.x != 1)
                direction = sf::Vector2i(-1, 0);
            else if (event.key.code == sf::Keyboard::Right && direction.x != -1)
                direction = sf::Vector2i(1, 0);
        }
    }
}

void Logic(sf::RenderWindow &window) {
    x += direction.x;
    y += direction.y;
    // Check for snake out of bounds
    if (x < 0 || x >= width || y < 0 || y >= height) {
        window.close();
        return;
    }
    snake.insert(snake.begin(), sf::Vector2i(x, y));
    if (x == fruitX && y == fruitY) {
        score++;
        fruitX = rand() % width;
        fruitY = rand() % height;
    } else {
        snake.pop_back();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(width * blockSize, height * blockSize), "Snake Game");

    Setup(window);

    while (window.isOpen()) {
        Input(window);
        Logic(window);
        Draw(window);
    }

    return 0;
}
