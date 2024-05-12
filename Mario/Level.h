#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "TileTypes.h"

struct Tile
{
    ETileTexture textureType;
    ETileCollision collisionType;
};

struct Level
{
    std::vector<std::vector<Tile>> tiles;
    std::map<ETileTexture,sf::Sprite> tileTextureTypeToSprite;

};

struct LevelDescriptor
{
    std::vector<std::vector<char>> levelSymbols;
    sf::Texture tileSetTexture;
    std::map<ETileTexture,sf::IntRect> tileTextureTypeToTextureRect;
};

Level CreateLevel (const LevelDescriptor& levelDescriptor, sf::Vector2f tileScale);