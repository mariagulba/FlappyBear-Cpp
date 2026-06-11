#include "InvalidNameScreen.h"

InvalidNameScreen::InvalidNameScreen(sf::Font& font)
    : backButton("Back", font, { 330, 250 }, sf::Color(128, 0, 32), sf::Color(180, 30, 60))
{
    message.setFont(font);
    message.setString("please enter a valid name\n   letters and digits only\n         up to 12 characters");
    message.setCharacterSize(40);
    message.setFillColor(sf::Color::Black);
    message.setPosition(20, 50);

}

void InvalidNameScreen::render(sf::RenderWindow& window) {
    window.draw(message);
    backButton.draw(window);
}

bool InvalidNameScreen::isBackClicked(sf::Vector2f mousePos) const {
    return backButton.isClicked(mousePos);
}
void InvalidNameScreen::updateHover(sf::Vector2f mousePos) {
    backButton.update(mousePos);
}