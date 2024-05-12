#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

enum class EPlayerDirection
{
    Left,
    Right
};


struct Player
{
    sf::Sprite playerSpite;
    sf::FloatRect playerRect;
    sf::Vector2f playerVelocity;
    float playerSpeed =220.f;
    float playerJumpSpeed=450.f;
    float playerKillEnemyJumpSpeed=200.f;
    bool bIsPlayerOnGround=false;
    int score=0;

    Animation idleAnimation;
    Animation walkAnimation;
    Animation jumpUpAnimation;
    Animation jumpDownAnimation;

    EPlayerDirection playerAnimationDirection=EPlayerDirection::Right;
    
    Animation* currentAnimation=nullptr;
};
