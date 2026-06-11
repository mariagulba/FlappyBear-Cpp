#pragma once
#include <SFML/Graphics.hpp>

class ButtonText {
private:
    sf::Text text;
    sf::Color defaultColor;
    sf::Color hoverColor;
    float defaultScale;
    float hoverScale;

public:
    ButtonText(const std::string& label, sf::Font& font, sf::Vector2f position,
        sf::Color defaultColor = sf::Color::White,
        sf::Color hoverColor = sf::Color(255, 255, 255, 180),
        float defaultScale = 1.f,
        float hoverScale = 1.1f);

    void update(sf::Vector2f mousePos);
    void draw(sf::RenderWindow& window) const;
    bool isClicked(sf::Vector2f mousePos) const;
    sf::FloatRect getGlobalBounds() const;

    void setCharacterSize(unsigned int size);
    void setFillColor(sf::Color color);
    void setPosition(sf::Vector2f pos);
};