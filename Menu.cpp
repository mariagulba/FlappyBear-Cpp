#include "Menu.h"
#include <iostream>

sf::Texture Menu::bearTexture;
Menu::Menu(sf::Font& font):startButton("Start New Game", font, { 230, 150 }, sf::Color(100, 50, 14), sf::Color(200, 100, 30)),
instructionButton("Instructions", font, { 255, 270 }, sf::Color(100, 50, 14), sf::Color(200, 100, 30)),
highScoreButton("High Scores", font, { 280, 210 }, sf::Color(100, 50, 14), sf::Color(200, 100, 30)),
exitButton("Exit", font, { 350, 330 }, sf::Color(128, 0, 32), sf::Color(180, 30, 60)) {

    title.setFont(font);
    title.setString("FLAPPY BEAR");
    title.setCharacterSize(80);
    title.setFillColor(sf::Color::White);
    title.setPosition(65, 10);

    

    if (!bearTexture.loadFromFile("assets/bear2.png")) {
        std::cerr << "Nie uda³o siê za³adowaæ bear2.png\n";
    }

    bear.setTexture(bearTexture);
    bear.setScale(0.25f, 0.25f);  // dopasuj wielkoœæ
    bear.setPosition(50.f, 420.f); // dolna czêœæ ekranu
    bearBaseY = 420.f;
    bearTimeOffset = 0.f;

    float spacing = 130.f;
    float startX = 230.f;
    float y = 500.f;

    for (int i = 0; i < 3; ++i) {
        sf::Sprite bee;
        bee.setTexture(PauseScreen::beeTexture);  // u¿ywasz globalnej tekstury z PauseScreen
        bee.setScale(0.4f, 0.4f);
        bee.setPosition(startX + i * spacing, y);

        bees.push_back(bee);
        baseY.push_back(y);
        timeOffsets.push_back(i * 0.5f);
    }


}

void Menu::render(sf::RenderWindow& window) {
    window.draw(title);
    startButton.draw(window);
    instructionButton.draw(window);
    highScoreButton.draw(window);
    exitButton.draw(window);
    window.draw(bear);

    for (const auto& bee : bees) {
        window.draw(bee);
    }
}

bool Menu::isStartClicked(sf::Vector2f mousePos) {
    return startButton.isClicked(mousePos);
}

bool Menu::isExitClicked(sf::Vector2f mousePos) {
    return exitButton.isClicked(mousePos);
}

bool Menu::isInstructionClicked(sf::Vector2f mousePos) {
    return instructionButton.isClicked(mousePos);
}

bool Menu::isHighScoreClicked(sf::Vector2f mousePos) {
    return highScoreButton.isClicked(mousePos);
}

void Menu::update(float deltaTime) {
    bearAnimationTime += deltaTime;
    float amplitude = 10.f;
    float speed = 2.0f;

    float offset = amplitude * std::sin((bearAnimationTime + bearTimeOffset) * speed);
    bear.setPosition(bear.getPosition().x, bearBaseY + offset);

    // animacja pszczó³
    beeAnimationTime += deltaTime;
    for (size_t i = 0; i < bees.size(); ++i) {
        float offsetY = amplitude * std::sin((beeAnimationTime + timeOffsets[i]) * speed);
        bees[i].setPosition(bees[i].getPosition().x, baseY[i] + offsetY);
    }
}

void Menu::updateHover(sf::Vector2f mousePos) {
    startButton.update(mousePos);
    exitButton.update(mousePos);
    instructionButton.update(mousePos);
    highScoreButton.update(mousePos);
}