#pragma once
#include <SFML/Graphics.hpp>

class Bird {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    float velocity;
    const float gravity = 0.5f;
    const float jumpStrength = -8.5f;

public:
    Bird();
    void jump();
    void update();
    void reset();
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
    float getY() const;
};