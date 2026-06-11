#include "Coin.h"
#include <iostream>

sf::Texture Coin::texture;

void Coin::loadTexture() {
    if (!texture.loadFromFile("assets/honey.png")) {
        std::cerr << "Nie uda³o siê za³adowaæ coin.png\n";
    }
}

Coin::Coin(float x, float y) : x(x) {
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setScale(0.3f, 0.3f);  // Dostosuj wielkoœæ do dziury
}

void Coin::update() {
    x -= 4;
    sprite.setPosition(x, sprite.getPosition().y);
}

void Coin::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

bool Coin::isOffScreen() const {
    return x + sprite.getGlobalBounds().width < 0;
}

bool Coin::checkCollision(const sf::FloatRect& birdBounds) const {
    return sprite.getGlobalBounds().intersects(birdBounds);
}

float Coin::getX() const {
    return x;
}
