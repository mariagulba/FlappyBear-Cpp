#include "InstructionScreen.h"

InstructionScreen::InstructionScreen(sf::Font& font)
    : backButton("Back", font, { 330, 330 }, sf::Color(128, 0, 32), sf::Color(180, 30, 60))
{
    title.setFont(font);
    title.setString("How to Play");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::White);
    title.setPosition(140, 10);

    content.setFont(font);
    content.setCharacterSize(20);
    content.setFillColor(sf::Color::Black);
    content.setPosition(210, 130);
    content.setString(
        "        Press SPACE to jump\n"
        "                  avoid trees\n"
        "do not fall to the ground\n"
        "\n"
        "             to score points\n"
        "            fly through gaps\n"
        "                collect honey  "
    );

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

void InstructionScreen::render(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(content);
    backButton.draw(window);
    for (const auto& bee : bees) {
        window.draw(bee);
    }
}
void InstructionScreen::update(float deltaTime) {
    beeAnimationTime += deltaTime;
    float amplitude = 10.f;
    float speed = 2.0f;

    for (size_t i = 0; i < bees.size(); ++i) {
        float offset = amplitude * std::sin((beeAnimationTime + timeOffsets[i]) * speed);
        bees[i].setPosition(bees[i].getPosition().x, baseY[i] + offset);
    }
}

bool InstructionScreen::isBackClicked(sf::Vector2f mousePos) const {
    return backButton.isClicked(mousePos);
}

void InstructionScreen::updateHover(sf::Vector2f mousePos) {
    backButton.update(mousePos);
}