#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>

using namespace std;

const int width = 40, height = 20, blockSize = 16;
int x = width/2-1, y = height/2-1;
int score = 0, fruitsEaten = 0;
float moveDelay = 0.12f, minDelay = 0.05f;
sf::Vector2i direction(1,0);
sf::Clock gameClock;
vector<sf::Vector2i> snake;
sf::Vector2i fruit(rand()%width, rand()%height);

void Setup(sf::RenderWindow &window) {
    window.setFramerateLimit(10);
    snake = {{x,y}};
    direction = {1,0};
    fruit = {rand()%width, rand()%height};
    score = fruitsEaten = 0;
    moveDelay = 0.12f;
}

void Draw(sf::RenderWindow &window) {
    window.clear(sf::Color::Black);

    for (auto &b : snake) {
        sf::RectangleShape block(sf::Vector2f(blockSize, blockSize));
        block.setPosition(b.x*blockSize, b.y*blockSize);
        block.setFillColor(sf::Color::Green);
        window.draw(block);
    }

    sf::RectangleShape f(sf::Vector2f(blockSize, blockSize));
    f.setPosition(fruit.x*blockSize, fruit.y*blockSize);
    f.setFillColor(sf::Color::Red);
    window.draw(f);

    window.display();
}

void Input(sf::RenderWindow &window) {
    sf::Event e;
    while(window.pollEvent(e)) {
        if(e.type==sf::Event::Closed) window.close();
        if(e.type==sf::Event::KeyPressed) {
            if(e.key.code==sf::Keyboard::Up && direction.y!=1) direction={0,-1};
            if(e.key.code==sf::Keyboard::Down && direction.y!=-1) direction={0,1};
            if(e.key.code==sf::Keyboard::Left && direction.x!=1) direction={-1,0};
            if(e.key.code==sf::Keyboard::Right && direction.x!=-1) direction={1,0};
        }
    }
}

void Logic(sf::RenderWindow &window) {
    if(gameClock.getElapsedTime().asSeconds()<moveDelay) return;
    gameClock.restart();

    x += direction.x;
    y += direction.y;
    sf::Vector2i newHead(x,y);
    if(x<0 || x>=width || y<0 || y>=height) { window.close(); return; }
    for(auto &b : snake) if(b==newHead) { window.close(); return; }

    snake.insert(snake.begin(), newHead);

    if(newHead==fruit) {
        score++;
        fruitsEaten++;
        fruit = {rand()%width, rand()%height};
        if(fruitsEaten%3==0 && moveDelay>minDelay) moveDelay -= 0.005f;
    } else {
        snake.pop_back();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(width*blockSize, height*blockSize), "Snake Game");
    Setup(window);

    while(window.isOpen()) {
        Input(window);
        Logic(window);
        Draw(window);
    }
}
