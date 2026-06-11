#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iostream> // potrzebne dla std::cerr

const int WIDTH = 800;
const int HEIGHT = 600;

Game::Game()
    : window(sf::VideoMode(WIDTH, HEIGHT), "FLAPPY BEAR"),

    menu(font),
    nameInput(font),
    gameOverScreen(font),
    instructionScreen(font),
    highScoreScreen(font),
    pauseScreen(font),
    hud(font),
    invalidNameScreen(font),
    state(State::Menu),
    score(0),
    gameRunning(false),
    hasStarted(false),
    countdownValue(3),
    backgroundX(0.0f)
{
    window.setFramerateLimit(60);
    Pipe::loadTextures();
    if (!PauseScreen::beeTexture.loadFromFile("assets/bee.png")) {
        std::cerr << "Nie uda³o siê za³adowaæ bee.png (globalnie)\n";
    }
    Coin::loadTexture();
    font.loadFromFile("baby-gemoy.regular.ttf");
    if (!screenTexture.loadFromFile("assets/screen.png")) {
        std::cerr << "Failed to load screen.png\n";
    }
    screenSprite.setTexture(screenTexture);

   
    if (!backgroundTexture.loadFromFile("assets/background.png")) {
        std::cerr << "Nie uda³o siê za³adowaæ t³a!\n";
    }

    backgroundSprite1.setTexture(backgroundTexture);
    backgroundSprite2.setTexture(backgroundTexture);

    backgroundSprite1.setPosition(0, 0);
    backgroundSprite2.setPosition(static_cast<float>(backgroundTexture.getSize().x), 0);

    menu = Menu(font);
    instructionScreen = InstructionScreen(font);
    highScoreScreen = HighScoreScreen(font);
    pauseScreen = PauseScreen(font);
    gameOverScreen = GameOverScreen(font);
    highScoreScreen.setScores(scoreManager.getTopScores());

    pressSpaceText.setFont(font);
    pressSpaceText.setCharacterSize(40);
    pressSpaceText.setFillColor(sf::Color(100, 50, 14));
    pressSpaceText.setString("Press SPACE to play");
    pressSpaceText.setPosition(100, 450);

    

    countdownText.setFont(font);
    countdownText.setCharacterSize(100);
    countdownText.setFillColor(sf::Color::White);
    countdownText.setPosition(360, 200);
    countdownText.setString("");

    srand(static_cast<unsigned>(time(nullptr)));

}

void Game::run() {
    sf::Clock deltaClock;
    while (window.isOpen()) {
        float dt = deltaClock.restart().asSeconds();

        handleEvents();

        if (state == State::Playing) update();
        else if (state == State::Resuming) updateCountdown();
        else if (state == State::Paused) pauseScreen.update(dt);
        else if (state == State::HighScores) highScoreScreen.update(dt);
        else if (state == State::Instruction) instructionScreen.update(dt);
        else if (state == State::Menu) menu.update(dt);
        else if (state == State::NameInput) nameInput.update(dt);
        else if (state == State::GameOver) gameOverScreen.update(dt);
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        switch (state) {
        case State::Menu:
            menu.updateHover(mousePos);
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (menu.isStartClicked(mousePos)) {
                    nameInput = NameInputScreen(font);
                    state = State::NameInput;
                }
                else if (menu.isExitClicked(mousePos)) {
                    window.close();
                }
                else if (menu.isInstructionClicked(mousePos)) {
                    state = State::Instruction;
                }
                else if (menu.isHighScoreClicked(mousePos)) {
                    highScoreScreen.setScores(scoreManager.getTopScores());
                    state = State::HighScores;
                }
            }
            break;

        case State::NameInput:
            nameInput.handleEvent(event);
            if (nameInput.isDone()) {
                if (nameInput.isValid()) {
                    playerName = nameInput.getName();
                    resetGame();
                    state = State::Playing;
                }
                else {
                    state = State::InvalidName;
                }
            }
            break;

        case State::InvalidName:
            invalidNameScreen.updateHover(mousePos);
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (invalidNameScreen.isBackClicked(mousePos)) {
                    nameInput = NameInputScreen(font);
                    state = State::NameInput;
                }
            }
            break;

        case State::Playing:
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    if (!hasStarted) {

                        hasStarted = true;
                    }
                    bird.jump();
                }
                else if (event.key.code == sf::Keyboard::Escape) {

                    state = State::Paused;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (hud.isPauseClicked(mousePos)) {

                    state = State::Paused;
                }
            }
            break;

        case State::Paused:
            pauseScreen.updateHover(mousePos);
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (pauseScreen.isResumeClicked(mousePos)) {
                    countdownValue = 3;
                    countdownText.setString("3");
                    countdownClock.restart();
                    state = State::Resuming;
                }
                else if (pauseScreen.isMainMenuClicked(mousePos)) {
                    state = State::Menu;
                }
            }
            break;

        case State::GameOver:
            gameOverScreen.updateHover(mousePos);
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (gameOverScreen.isPlayAgainClicked(mousePos)) {
                    resetGame();
                    state = State::Playing;
                }
                else if (gameOverScreen.isMainMenuClicked(mousePos)) {
                    state = State::Menu;
                }
            }
            break;

        case State::Instruction:
            instructionScreen.updateHover(mousePos);
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (instructionScreen.isBackClicked(mousePos)) {
                    state = State::Menu;
                }
            }
            break;

        case State::HighScores:
            highScoreScreen.updateHover(mousePos);
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (highScoreScreen.isBackClicked(mousePos)) {
                    state = State::Menu;
                }
            }
            break;

        default:
            break;
        }
    }
}

void Game::update() {
    if (!hasStarted || state != State::Playing) return;

    
    backgroundX -= backgroundScrollSpeed;
    if (backgroundX <= -static_cast<float>(backgroundTexture.getSize().x)) {
        backgroundX = 0;
    }
    backgroundSprite1.setPosition(backgroundX, 0);
    backgroundSprite2.setPosition(backgroundX + backgroundTexture.getSize().x, 0);

    bird.update();
    hud.update(score);

    if (pipeClock.getElapsedTime().asSeconds() > 2.0f) {
        pipeClock.restart();
        spawnPipe();
    }

    for (auto& pipe : pipes) {
        pipe->update();

        if (pipe->checkCollision(bird.getBounds())) {
            state = State::GameOver;
            scoreManager.submitScore(playerName, score);
            gameOverScreen.setScores(scoreManager.getTopScores());
            gameOverScreen.setFinalScore(score);
        }

        // zbieranie monety (tylko jeœli to PipeWithCoin)
        if (auto* withCoin = dynamic_cast<PipeWithCoin*>(pipe.get())) {
            if (withCoin->checkCoinCollision(bird.getBounds())) {
                score++;
            }
        }

        if (pipe->getX() + pipe->getWidth() == static_cast<int>(bird.getBounds().left)) {
            score++;
        }
    }

    if (!pipes.empty() && pipes.front()->isOffScreen()) {
        pipes.erase(std::remove_if(pipes.begin(), pipes.end(),
            [](const std::unique_ptr<Pipe>& pipe) {
                return pipe->isOffScreen();
            }), pipes.end());
    }

    if (bird.getY() < 0 || bird.getBounds().top + bird.getBounds().height > HEIGHT) {
        state = State::GameOver;
        scoreManager.submitScore(playerName, score);
        gameOverScreen.setScores(scoreManager.getTopScores());
        gameOverScreen.setFinalScore(score);
    }
    if (!hasStarted) {
        pressTextTime += 0.05f;

        if (pressTextTime >= 0.6f) { // co 0.6 sekundy zmiana widocznoœci
            pressTextVisible = !pressTextVisible;
            pressTextTime = 0.f;
        }
    }
}

void Game::updateCountdown() {
    if (countdownClock.getElapsedTime().asSeconds() >= 1.0f) {
        countdownValue--;
        if (countdownValue <= 0) {
            countdownText.setString("");

            pipeClock.restart();
            state = State::Playing;
        }
        else {
            countdownText.setString(std::to_string(countdownValue));
            countdownClock.restart();
        }
    }
}

void Game::render() {
    window.clear();

    // Rysowanie t³a
    window.draw(backgroundSprite1);
    window.draw(backgroundSprite2);

    switch (state) {
    case State::Menu:
        window.draw(screenSprite);
        menu.render(window);
        break;
    case State::NameInput:
        window.draw(screenSprite);
        nameInput.render(window);
        break;
    case State::InvalidName:
        window.draw(screenSprite);
        invalidNameScreen.render(window);
        break;
    case State::Playing:
        bird.draw(window);
        for (auto& pipe : pipes) pipe->draw(window);
        hud.render(window);
        if (!hasStarted && pressTextVisible)
            window.draw(pressSpaceText);
        break;
    case State::GameOver:
        window.draw(screenSprite);
        gameOverScreen.render(window);
        break;
    case State::Instruction:
        window.draw(screenSprite);
        instructionScreen.render(window);
        break;
    case State::HighScores:
        window.draw(screenSprite);
        highScoreScreen.render(window);
        break;
    case State::Paused:
        window.draw(screenSprite);
        pauseScreen.render(window);
        break;
    case State::Resuming:
        bird.draw(window);
        for (auto& pipe : pipes) pipe->draw(window);
        hud.render(window);
        window.draw(countdownText);
        break;
    }

    window.display();
}
void Game::spawnPipe() {
    int gapY = rand() % (HEIGHT - 200) + 50;

    if (rand() % 100 < 30) {
        pipes.push_back(std::make_unique<PipeWithCoin>(gapY));
    }
    else {
        pipes.push_back(std::make_unique<Pipe>(gapY));
    }
}

void Game::resetGame() {
    bird.reset();
    pipes.clear();
    score = 0;
    pipeClock.restart();
    hasStarted = false;
    hud.update(0);
}