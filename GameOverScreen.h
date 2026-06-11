#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "ButtonText.h"
#include "PauseScreen.h"

class GameOverScreen {
private:
    sf::Text title;
    ButtonText playAgainButton;
    ButtonText mainMenuButton;
    std::vector<sf::Text> scoreEntries;
    sf::Text finalScore;

    std::vector<sf::Sprite> bees;
    std::vector<float> baseY;
    std::vector<float> timeOffsets;
    float beeAnimationTime = 0.f;
public:
    GameOverScreen(sf::Font& font);
    void setScores(const std::vector<std::pair<std::string, int>>& scores);
    void render(sf::RenderWindow& window);
    void setFinalScore(int score);
    bool isPlayAgainClicked(sf::Vector2f mousePos);
    bool isMainMenuClicked(sf::Vector2f mousePos);
    void updateHover(sf::Vector2f mousePos);
    void update(float deltaTime);
};