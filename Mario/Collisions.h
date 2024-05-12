#pragma once

#include <SFML/Graphics.hpp>
#include "Level.h"

enum class EOrientation
{
    Horizontal,
    Vertical
};

struct CollisionResult
{
    bool bisCollided=false;
    sf::Vector2f newPosition;
};


CollisionResult HandleCollision(
    const sf::FloatRect& objectRect,
    const sf::Vector2f& objectVelocity,
    const Level& level,
    EOrientation orientation,
    const sf::Vector2f& tileSize);