#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Animation
{
public:
    void Update(float DeltaSeconds);
    int GetCurrentFrameIndex();
    const sf::IntRect& GetCurrentFrame();

public:
    sf::Texture texture;
    std::vector<sf::IntRect> frames;
    float speed=1.f;
    
private:
    float currentFrameIndex=0.f;
};
