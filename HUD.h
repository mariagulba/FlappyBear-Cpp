#pragma once
#include <SFML/Graphics.hpp>

class HUD {
private:
    sf::Text scoreText;
    sf::Texture pauseTexture;
    sf::Sprite pauseSprite;
    sf::Text scoreLabel;

public:
    HUD(sf::Font& font);
    void update(int score);
    void render(sf::RenderWindow& window);
    bool isPauseClicked(sf::Vector2f mousePos) const;
};