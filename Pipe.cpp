#include "Pipe.h"
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;

// Definicje statycznych tekstur
sf::Texture Pipe::topTexture;
sf::Texture Pipe::bottomTexture;

void Pipe::loadTextures() {
    if (!topTexture.loadFromFile("assets/pipe_top.png")) {
        std::cerr << "Nie uda³o siê za³adowaæ pipe_top.png\n";
    }
    if (!bottomTexture.loadFromFile("assets/pipe_bottom.png")) {
        std::cerr << "Nie uda³o siê za³adowaæ pipe_bottom.png\n";
    }
}

Pipe::Pipe(int gapY) {
    x = WIDTH;

    top.setTexture(topTexture);
    bottom.setTexture(bottomTexture);

    // Pozycje rur
    top.setPosition(x, gapY - top.getGlobalBounds().height); // górna rura wystaje z góry
    bottom.setPosition(x, gapY + gapSize);                   // dolna rura
}

void Pipe::update() {
    x -= 4;
    top.setPosition(x, top.getPosition().y);
    bottom.setPosition(x, bottom.getPosition().y);
}

void Pipe::draw(sf::RenderWindow& window) const {
    window.draw(top);
    window.draw(bottom);
}

bool Pipe::isOffScreen() const {
    return top.getGlobalBounds().left + top.getGlobalBounds().width < 0 &&
        bottom.getGlobalBounds().left + bottom.getGlobalBounds().width < 0;
}

bool Pipe::checkCollision(const sf::FloatRect& birdBounds) const {
    return birdBounds.intersects(top.getGlobalBounds()) || birdBounds.intersects(bottom.getGlobalBounds());
}

float Pipe::getX() const {
    return x;
}

int Pipe::getWidth() const {
    return width;
}