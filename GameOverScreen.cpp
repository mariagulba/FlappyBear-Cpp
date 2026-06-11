#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(sf::Font& font)
    : playAgainButton("Play Again", font, { 270, 280 }, sf::Color(100, 50, 14), sf::Color(200, 100, 30)),
    mainMenuButton("Main Menu", font, { 270, 330 }, sf::Color(128, 0, 32), sf::Color(180, 30, 60))
{
    title.setFont(font);
    title.setString("GAME OVER");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::White);
    title.setPosition(180, 10);

    finalScore.setFont(font);
    finalScore.setCharacterSize(30);
    finalScore.setFillColor(sf::Color::Black);
    finalScore.setPosition(250, 220);


    for (int i = 0; i < 3; ++i) {
        sf::Text entry;
        entry.setFont(font);
        entry.setCharacterSize(25);
        entry.setFillColor(sf::Color(120, 120, 120));
        entry.setPosition(250, 100 + i * 30);
        scoreEntries.push_back(entry);
    }
    float spacing = 130.f;
    float startX = 230.f;
    float y = 500.f;

    for (int i = 0; i < 3; ++i) {
        sf::Sprite bee;
        bee.setTexture(PauseScreen::beeTexture);  // u¿yj globalnej tekstury
        bee.setScale(0.4f, 0.4f);
        bee.setPosition(startX + i * spacing, y);

        bees.push_back(bee);
        baseY.push_back(y);
        timeOffsets.push_back(i * 0.5f);
    }
}

void GameOverScreen::setScores(const std::vector<std::pair<std::string, int>>& scores) {
    for (int i = 0; i < scoreEntries.size(); ++i) {
        if (i < scores.size()) {
            scoreEntries[i].setString(std::to_string(i + 1) + ". " + scores[i].first + "   " + std::to_string(scores[i].second));
        }
        else {
            scoreEntries[i].setString("");
        }
    }
}

void GameOverScreen::render(sf::RenderWindow& window) {
    window.draw(title);
    playAgainButton.draw(window);
    mainMenuButton.draw(window);
    window.draw(finalScore);
    for (const auto& entry : scoreEntries) window.draw(entry);

    for (const auto& bee : bees) {
        window.draw(bee);
    }

}
void GameOverScreen::setFinalScore(int score) {
    finalScore.setString("Your score: " + std::to_string(score));
}

bool GameOverScreen::isPlayAgainClicked(sf::Vector2f mousePos) {
    return playAgainButton.isClicked(mousePos);
}

bool GameOverScreen::isMainMenuClicked(sf::Vector2f mousePos) {
    return mainMenuButton.isClicked(mousePos);
}

void GameOverScreen::updateHover(sf::Vector2f mousePos) {
    playAgainButton.update(mousePos);
    mainMenuButton.update(mousePos);
}
void GameOverScreen::update(float deltaTime) {
    beeAnimationTime += deltaTime;
    float amplitude = 10.f;
    float speed = 2.0f;

    for (size_t i = 0; i < bees.size(); ++i) {
        float offsetY = amplitude * std::sin((beeAnimationTime + timeOffsets[i]) * speed);
        bees[i].setPosition(bees[i].getPosition().x, baseY[i] + offsetY);
    }
}