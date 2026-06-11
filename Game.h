#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>

#include "Bird.h"
#include "Pipe.h"
#include "PipeWithCoin.h"
#include "Menu.h"
#include "NameInputScreen.h"
#include "GameOverScreen.h"
#include "ScoreManager.h"
#include "InstructionScreen.h"
#include "PauseScreen.h"
#include "HUD.h"
#include "HighScoreScreen.h"
#include "InvalidNameScreen.h"
#include "Coin.h"

class Game {
private:
    enum class State {
        Menu,
        NameInput,
        Playing,
        GameOver,
        Instruction,
        HighScores,
        Paused,
        Resuming,
        InvalidName
    };

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite1;
    sf::Sprite backgroundSprite2;
    sf::Texture screenTexture;
    sf::Sprite screenSprite;
    float backgroundX;
    const float backgroundScrollSpeed = 1.0f;

    sf::RenderWindow window;
    sf::Font font;

    Bird bird;
    std::vector<std::unique_ptr<Pipe>> pipes;

    sf::Clock pipeClock;


    Menu menu;
    NameInputScreen nameInput;
    GameOverScreen gameOverScreen;
    InstructionScreen instructionScreen;
    HighScoreScreen highScoreScreen;
    InvalidNameScreen invalidNameScreen;

    ScoreManager scoreManager;
    PauseScreen pauseScreen;
    HUD hud;

    sf::Text pressSpaceText;
    float pressTextTime = 0.f;
    bool pressTextVisible = true;
    sf::Text countdownText;
    sf::Clock countdownClock;
    int countdownValue;

    State state;
    std::string playerName;
    int score;
    bool gameRunning;
    bool hasStarted;
    sf::Clock pauseClock;

public:
    Game();
    void run();

private:
    void handleEvents();
    void update();
    void updateCountdown();
    void render();
    void resetGame();
    void spawnPipe();
};