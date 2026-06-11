#include "Bird.h"
#include <iostream>  

const int HEIGHT = 600;

Bird::Bird() {
    if (!texture.loadFromFile("assets/bear.png")) {
        std::cerr << "Nie uda³o siê za³adowaæ bear.png\n";
    }

    sprite.setTexture(texture);
    sprite.setPosition(100, HEIGHT / 2);
    sprite.setScale(0.2f, 0.2f); 
    velocity = 0;
}

void Bird::jump() {
    velocity = jumpStrength;
}

void Bird::update() {
    velocity += gravity;
    sprite.move(0, velocity);
}

void Bird::reset() {
    sprite.setPosition(100, HEIGHT / 2);
    velocity = 0;
}

void Bird::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Bird::getBounds() const {
    return sprite.getGlobalBounds();
}

float Bird::getY() const {
    return sprite.getPosition().y;
}