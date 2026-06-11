#include "NameInputScreen.h"
#include <regex>
#include <iostream>

sf::Texture NameInputScreen::instructionTexture;
NameInputScreen::NameInputScreen(sf::Font& font) : done(false) {
    prompt.setFont(font);
    prompt.setString("Enter Your Name");
    prompt.setCharacterSize(40);
    prompt.setFillColor(sf::Color::White);
    prompt.setPosition(150, 130);

    inputText.setFont(font);
    inputText.setCharacterSize(30);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(200, 200);

    if (!instructionTexture.loadFromFile("assets/instruction.png")) {
        std::cerr << "Nie uda³o siê za³adowaæ instruction.png\n";
    }
    instructionSprite.setTexture(instructionTexture);
    instructionSprite.setScale(0.4f, 0.4f);  // Dostosuj jak chcesz
    instructionSprite.setPosition(20.f, 10.f);  // Dowolne miejsce
    baseY = 280.f;

    cursor.setSize(sf::Vector2f(2.f, 30.f));  // szerokoœæ i wysokoœæ kursora
    cursor.setFillColor(sf::Color::Black);
    cursor.setPosition(inputText.getPosition().x, inputText.getPosition().y);
}

void NameInputScreen::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b' && !playerName.empty()) {
            playerName.pop_back();
        }
        else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
            done = true;  // walidacja bêdzie poza klas¹
        }
        else if (event.text.unicode < 128 && playerName.size() < 50) {
            char c = static_cast<char>(event.text.unicode);
            playerName += c;  // dodaj bez sprawdzania
        }
        inputText.setString(playerName);
    }
}

void NameInputScreen::render(sf::RenderWindow& window) {
    window.draw(prompt);
    inputText.setString(playerName);
    window.draw(inputText);
    if (cursorVisible) {
        window.draw(cursor);
    }
    window.draw(instructionSprite);
}

std::string NameInputScreen::getName() const {
    return playerName;
}

bool NameInputScreen::isDone() const {
    return done;
}

bool NameInputScreen::isValid() const {
    std::regex pattern("^[A-Za-z0-9]{1,12}$");
    return std::regex_match(playerName, pattern);
}
void NameInputScreen::update(float deltaTime) {
    animationTime += deltaTime;
    float amplitude = 10.f;
    float speed = 2.0f;
    float offset = amplitude * std::sin(animationTime * speed);
    instructionSprite.setPosition(instructionSprite.getPosition().x, baseY + offset);

    cursorTimer += deltaTime;
    if (cursorTimer >= 0.5f) {
        cursorVisible = !cursorVisible;
        cursorTimer = 0.f;
    }
    sf::FloatRect textBounds = inputText.getGlobalBounds();
    cursor.setPosition(textBounds.left + textBounds.width + 2.f, textBounds.top);
}