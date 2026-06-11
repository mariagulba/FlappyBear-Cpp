#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class NameInputScreen {
private:
    sf::Text prompt;
    sf::Text inputText;
    std::string playerName;
    bool done;
    static sf::Texture instructionTexture;
    sf::Sprite instructionSprite;
    float baseY;
    float animationTime = 0.f;

    sf::RectangleShape cursor;
    bool cursorVisible = true;
    float cursorTimer = 0.f;

public:
    NameInputScreen(sf::Font& font);
    void handleEvent(const sf::Event& event);
    void render(sf::RenderWindow& window);
    std::string getName() const;
    bool isDone() const;
    bool isValid() const; // <-- dodane
    void update(float deltaTime);

};