#include "HighScoreScreen.h"

HighScoreScreen::HighScoreScreen(sf::Font& font)
    : backButton("Back", font, { 340, 300 }, sf::Color(128, 0, 32), sf::Color(180, 30, 60))
{
    title.setFont(font);
    title.setString("HIGH SCORES");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::White);
    title.setPosition(160, 50);


    for (int i = 0; i < 3; ++i) {
        sf::Text entry;
        entry.setFont(font);
        entry.setCharacterSize(25);
        entry.setFillColor(sf::Color::Black);
        entry.setPosition(270, 160 + i * 30);
        scoreEntries.push_back(entry);
    }
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

void HighScoreScreen::setScores(const std::vector<std::pair<std::string, int>>& scores) {
    for (int i = 0; i < scoreEntries.size(); ++i) {
        if (i < scores.size()) {
            scoreEntries[i].setString(std::to_string(i + 1) + ". " + scores[i].first + "   " + std::to_string(scores[i].second));
        }
        else {
            scoreEntries[i].setString("");
        }
    }
}

void HighScoreScreen::render(sf::RenderWindow& window) {
    window.draw(title);
    for (const auto& entry : scoreEntries)
        window.draw(entry);
    backButton.draw(window);
    for (const auto& bee : bees) {
        window.draw(bee);
    }
}

bool HighScoreScreen::isBackClicked(sf::Vector2f mousePos) const {
    return backButton.isClicked(mousePos);
}
void HighScoreScreen::update(float deltaTime) {
    beeAnimationTime += deltaTime;
    float amplitude = 10.f;
    float speed = 2.0f;

    for (size_t i = 0; i < bees.size(); ++i) {
        float offset = amplitude * std::sin((beeAnimationTime + timeOffsets[i]) * speed);
        bees[i].setPosition(bees[i].getPosition().x, baseY[i] + offset);
    }
}
void HighScoreScreen::updateHover(sf::Vector2f mousePos) {
    backButton.update(mousePos);
}