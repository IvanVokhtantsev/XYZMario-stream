#include "Collisions.h"

CollisionResult HandleCollision(
    const sf::FloatRect& objectRect,
    const sf::Vector2f& objectVelocity,
    const Level& level,
    EOrientation orientation,
    const sf::Vector2f& tileSize)
{
    const int xLeftTile=objectRect.left/tileSize.x;
    const int xRightTile=(objectRect.left+objectRect.width-1)/tileSize.x;

    
    const int yTopTile=objectRect.top/tileSize.y;
    const int yBottomTile=(objectRect.top+objectRect.height-1)/tileSize.y;

    CollisionResult result;
    result.newPosition=objectRect.getPosition();
    
    for (int i=yTopTile; i<=yBottomTile; ++i)
    {
        for (int j=xLeftTile; j<=xRightTile; ++j)
        {
            const Tile& tile=level.tiles[i][j];
            auto tilePosition=sf::Vector2f(j*tileSize.x,i*tileSize.y);
            if (tile.collisionType==ETileCollision::Collision)
            {
                result.bisCollided=true;
                if (orientation==EOrientation::Horizontal)
                {
                    if (objectVelocity.x<0)
                    {
                        result.newPosition=sf::Vector2f(tilePosition.x+tileSize.x,objectRect.top); 
                    }
                    else
                    {
                        result.newPosition=sf::Vector2f(tilePosition.x-objectRect.width,objectRect.top); 
                    }
                    
                }
                else
                {
                    if (objectVelocity.y<0)
                    {
                        result.newPosition=sf::Vector2f(objectRect.left,tilePosition.y-objectRect.height);
                    }
                    else
                    {
                        result.newPosition=sf::Vector2f(objectRect.left,tilePosition.y+tileSize.y); 
                    }
                }
                return result;
            }
        }
    }
    return result;
}