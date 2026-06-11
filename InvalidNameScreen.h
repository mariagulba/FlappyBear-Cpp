#pragma once
#include <SFML/Graphics.hpp>
#include "ButtonText.h"

class InvalidNameScreen {
private:
    sf::Text message;
    ButtonText backButton;

public:
    InvalidNameScreen(sf::Font& font);
    void render(sf::RenderWindow& window);
    bool isBackClicked(sf::Vector2f mousePos) const;
    void updateHover(sf::Vector2f mousePos);
};