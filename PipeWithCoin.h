#pragma once
#include "Pipe.h"
#include "Coin.h"

class PipeWithCoin : public Pipe {
private:
    Coin coin;
    bool collected;

public:
    PipeWithCoin(int gapY);

    void update() override;
    void draw(sf::RenderWindow& window) const override;
    bool checkCollision(const sf::FloatRect& birdBounds) const override;
    bool checkCoinCollision(const sf::FloatRect& birdBounds); 
};