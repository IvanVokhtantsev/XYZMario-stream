#include "Level.h"

Level CreateLevel (const LevelDescriptor& levelDescriptor, sf::Vector2f tileScale)
{
    Level level;

    for (int i=0; i<levelDescriptor.levelSymbols.size();++i)
    {
        level.tiles.push_back({});
        for (int j=0; j<levelDescriptor.levelSymbols[i].size(); ++j)
        {
            Tile tile;
            if (levelDescriptor.levelSymbols[i][j]=='B')
            {
                tile.textureType=ETileTexture::Ground;
                tile.collisionType=ETileCollision::Collision;
            }
            if (levelDescriptor.levelSymbols[i][j]=='S')
            {
                tile.textureType=ETileTexture::Empty;
                tile.collisionType=ETileCollision::NoCollision;
            }
            level.tiles[i].push_back(tile);
        }
    }
    for (const auto& tileTextureTypeToRect:levelDescriptor.tileTextureTypeToTextureRect)
    {
        sf::Sprite sprite;
        sprite.setTexture(levelDescriptor.tileSetTexture);
        sprite.setTextureRect(tileTextureTypeToRect.second);
        sprite.setScale(tileScale);
        level.tileTextureTypeToSprite[tileTextureTypeToRect.first]=sprite;
    } 
    return level;
}