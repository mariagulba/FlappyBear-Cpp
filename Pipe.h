#pragma once
#include <SFML/Graphics.hpp>

class Pipe {
private:
    static sf::Texture topTexture;
    static sf::Texture bottomTexture;
    sf::Sprite top;
    sf::Sprite bottom;
    float x;
    static constexpr int width = 60;
    static constexpr int gapSize = 200;

public:
    static void loadTextures(); 
    static int getGapSize() { return gapSize; }
    static int getPipeWidth() { return width; }
    Pipe(int gapY);

   virtual  void update();
   virtual void draw(sf::RenderWindow& window) const;
   virtual bool isOffScreen() const;
   virtual bool checkCollision(const sf::FloatRect& birdBounds) const;

    float getX() const;
    int getWidth() const;

    virtual ~Pipe() = default;
};