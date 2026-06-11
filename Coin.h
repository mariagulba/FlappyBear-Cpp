#pragma once
#include <SFML/Graphics.hpp>

class Coin {
private:
    sf::Sprite sprite;
    static sf::Texture texture;
    float x;

public:
    static void loadTexture();
    Coin(float x, float y);
    void update();
    void draw(sf::RenderWindow& window) const;
    bool isOffScreen() const;
    bool checkCollision(const sf::FloatRect& birdBounds) const;
    float getX() const;
};