#include "PipeWithCoin.h"

PipeWithCoin::PipeWithCoin(int gapY)
    : Pipe(gapY),
    coin(getX() + getPipeWidth() / 2.0f - 15, gapY + Pipe::getGapSize() / 2.0f - 15),
    collected(false) {
}

void PipeWithCoin::update() {
    Pipe::update();
    coin.update();
}

void PipeWithCoin::draw(sf::RenderWindow& window) const {
    Pipe::draw(window);
    if (!collected) {
        coin.draw(window);
    }
}

bool PipeWithCoin::checkCollision(const sf::FloatRect& birdBounds) const {
    return Pipe::checkCollision(birdBounds);
}

bool PipeWithCoin::checkCoinCollision(const sf::FloatRect& birdBounds) {
    if (!collected && coin.checkCollision(birdBounds)) {
        collected = true;
        return true;
    }
    return false;
}