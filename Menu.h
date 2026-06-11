#pragma once
#include <SFML/Graphics.hpp>
#include "ButtonText.h"
#include "PauseScreen.h"

class Menu {
private:
    sf::Text title;
    ButtonText startButton;
    ButtonText exitButton;
    ButtonText instructionButton;
    ButtonText highScoreButton;
    sf::Sprite bear;
    float bearBaseY;
    float bearTimeOffset;
    float bearAnimationTime = 0.f;

    static sf::Texture bearTexture;
    std::vector<sf::Sprite> bees;
    std::vector<float> baseY;
    std::vector<float> timeOffsets;
    float beeAnimationTime = 0.f;


public:
    Menu(sf::Font& font);
    void render(sf::RenderWindow& window);
    bool isStartClicked(sf::Vector2f mousePos);
    bool isExitClicked(sf::Vector2f mousePos);
    bool isInstructionClicked(sf::Vector2f mousePos);
    bool isHighScoreClicked(sf::Vector2f mousePos);
    void update(float deltaTime);
    void updateHover(sf::Vector2f mousePos);
};