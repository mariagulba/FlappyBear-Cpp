#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "PauseScreen.h"
#include "ButtonText.h"
class InstructionScreen {
private:
    sf::Text title;
    sf::Text content;
    ButtonText backButton;

    std::vector<sf::Sprite> bees;
    std::vector<float> baseY;
    std::vector<float> timeOffsets;
    float beeAnimationTime = 0.f;

public:
    InstructionScreen(sf::Font& font);
    void render(sf::RenderWindow& window);
    bool isBackClicked(sf::Vector2f mousePos) const;
    void update(float deltaTime);
    void updateHover(sf::Vector2f mousePos);
};