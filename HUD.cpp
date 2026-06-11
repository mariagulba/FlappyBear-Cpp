#include "HUD.h"
#include <cstdio>
#include <iostream>

HUD::HUD(sf::Font& font) {
    scoreLabel.setFont(font);
    scoreLabel.setCharacterSize(25);
    scoreLabel.setFillColor(sf::Color::White);  // bia³y napis
    scoreLabel.setString("Score");
    scoreLabel.setPosition(20, 20); 

    scoreText.setFont(font);
    scoreText.setCharacterSize(60);
    scoreText.setFillColor(sf::Color(250, 190, 80));
    scoreText.setPosition(50,55);

    if (!pauseTexture.loadFromFile("assets/pause.png")) {
        std::cerr << "Nie uda³o siê za³adowaæ pause.png\n";
    }

    pauseSprite.setTexture(pauseTexture);
    pauseSprite.setScale(0.5f, 0.5f); // dopasuj rozmiar jeœli trzeba
    pauseSprite.setPosition(700, 0);
}

void HUD::update(int score) {
    scoreText.setString(std::to_string(score));
}

void HUD::render(sf::RenderWindow& window) {
    window.draw(scoreText);
    window.draw(scoreLabel);
    window.draw(pauseSprite);
}

bool HUD::isPauseClicked(sf::Vector2f mousePos) const {
    return pauseSprite.getGlobalBounds().contains(mousePos);
}