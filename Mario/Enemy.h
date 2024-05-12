#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
struct Enemy
{
    StaticObject staticObj;
    sf::Vector2f enemyVelocity;
    float enemySpeed =220.f;
    bool bDead=false;
    
};
