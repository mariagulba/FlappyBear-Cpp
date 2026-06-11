#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "PauseScreen.h"
#include "ButtonText.h"

class HighScoreScreen {
private:
    sf::Text title;
    ButtonText backButton;
    std::vector<sf::Text> scoreEntries;

    std::vector<sf::Sprite> bees;
    std::vector<float> baseY;
    std::vector<float> timeOffsets;
    float beeAnimationTime = 0.f;

public:
    HighScoreScreen(sf::Font& font);
    void setScores(const std::vector<std::pair<std::string, int>>& scores);
    void render(sf::RenderWindow& window);
    bool isBackClicked(sf::Vector2f mousePos) const;
    void update(float deltaTime);
    void updateHover(sf::Vector2f mousePos);
};