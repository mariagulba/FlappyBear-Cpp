#include "ButtonText.h"

ButtonText::ButtonText(const std::string& label, sf::Font& font, sf::Vector2f position,
    sf::Color defaultColor, sf::Color hoverColor,
    float defaultScale, float hoverScale)
    : defaultColor(defaultColor), hoverColor(hoverColor),
    defaultScale(defaultScale), hoverScale(hoverScale)
{
    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(30);
    text.setFillColor(defaultColor);
    text.setPosition(position);
    text.setScale(defaultScale, defaultScale);
}

void ButtonText::update(sf::Vector2f mousePos) {
    if (text.getGlobalBounds().contains(mousePos)) {
        text.setFillColor(hoverColor);
        text.setScale(hoverScale, hoverScale);
    }
    else {
        text.setFillColor(defaultColor);
        text.setScale(defaultScale, defaultScale);
    }
}

void ButtonText::draw(sf::RenderWindow& window) const {
    window.draw(text);
}

bool ButtonText::isClicked(sf::Vector2f mousePos) const {
    return text.getGlobalBounds().contains(mousePos);
}

sf::FloatRect ButtonText::getGlobalBounds() const {
    return text.getGlobalBounds();
}

void ButtonText::setCharacterSize(unsigned int size) {
    text.setCharacterSize(size);
}

void ButtonText::setFillColor(sf::Color color) {
    defaultColor = color;
    text.setFillColor(color);
}

void ButtonText::setPosition(sf::Vector2f pos) {
    text.setPosition(pos);
}