#include "PauseScreen.h"
#include <iostream>

sf::Texture PauseScreen::beeTexture;
PauseScreen::PauseScreen(sf::Font& font) : resumeButton("Resume", font, { 305, 200 }, sf::Color(100, 50, 14), sf::Color(200, 100, 30)),
mainMenuButton("Main Menu", font, { 270, 260 }, sf::Color(100, 50, 14), sf::Color(200, 100, 30)) {
    title.setFont(font);
    title.setString("Game Paused");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::White);
    title.setPosition(130, 60);

    float spacing = 130.f;
    float startX = 230.f;
    float y = 500.f;

    for (int i = 0; i < 3; ++i) {
        sf::Sprite bee;
        bee.setTexture(PauseScreen::beeTexture);
        bee.setScale(0.4f, 0.4f);
        bee.setPosition(startX + i * spacing, y);

        bees.push_back(bee);
        baseY.push_back(y);
        timeOffsets.push_back(i * 0.5f);
    }
}

void PauseScreen::render(sf::RenderWindow& window) {
    window.draw(title);
    resumeButton.draw(window);
    mainMenuButton.draw(window);
    for (const auto& bee : bees) {
        window.draw(bee);
    }
}
void PauseScreen::update(float deltaTime) {
    beeAnimationTime += deltaTime;
    float amplitude = 10.f;
    float speed = 2.0f;

    for (size_t i = 0; i < bees.size(); ++i) {
        float offsetY = amplitude * std::sin((beeAnimationTime + timeOffsets[i]) * speed);
        bees[i].setPosition(bees[i].getPosition().x, baseY[i] + offsetY);
    }
}

bool PauseScreen::isResumeClicked(sf::Vector2f mousePos) const {
    return resumeButton.isClicked(mousePos);
}

bool PauseScreen::isMainMenuClicked(sf::Vector2f mousePos) const {
    return mainMenuButton.isClicked(mousePos);
}
void PauseScreen::updateHover(sf::Vector2f mousePos) {
    resumeButton.update(mousePos);
    mainMenuButton.update(mousePos);
}