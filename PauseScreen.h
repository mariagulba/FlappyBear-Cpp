#pragma once
#include <SFML/Graphics.hpp>
#include "ButtonText.h"

class PauseScreen {
public:
    static sf::Texture beeTexture;
    
private:
    sf::Text title;
    ButtonText resumeButton;
    ButtonText mainMenuButton;

    std::vector<sf::Sprite> bees;
    std::vector<float> baseY;
    std::vector<float> timeOffsets;
    float beeAnimationTime = 0;


public:

    PauseScreen(sf::Font& font);
    void render(sf::RenderWindow& window);
    bool isResumeClicked(sf::Vector2f mousePos) const;
    bool isMainMenuClicked(sf::Vector2f mousePos) const;
    void update(float deltaTime);
    void updateHover(sf::Vector2f mousePos);

};