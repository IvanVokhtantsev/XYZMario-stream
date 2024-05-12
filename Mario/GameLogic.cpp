#include "GameLogic.h"
#include "Collisions.h"

void HandleInput(Player&player)
{
    player.playerVelocity.x=0.f;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        player.playerVelocity.x=-player.playerSpeed;  
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        player.playerVelocity.x=player.playerSpeed;  
    }
}
void HandleWindowsEvent(const sf::Event&event, Player&player)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code==sf::Keyboard::Space)
        {
            if (player.bIsPlayerOnGround)
            {
                player.bIsPlayerOnGround=false;
                player.playerVelocity.y=player.playerJumpSpeed;
            }
        }
    }
}

void UpdateGame(World&world, float clockDeltaSeconds,const sf::Vector2f&tileSize)
{
    {
        for (Enemy&enemy:world.enemies)
        {
            if (!enemy.bDead)
            {
                enemy.staticObj.rect.left+=enemy.enemyVelocity.x*clockDeltaSeconds;
                CollisionResult collisionResult=HandleCollision(enemy.staticObj.rect,enemy.enemyVelocity,world.level,EOrientation::Horizontal,tileSize);
                if(collisionResult.bisCollided)
                {
                    enemy.staticObj.rect.left=collisionResult.newPosition.x;
                    enemy.enemyVelocity.x *=-1;
                }
            }
        }
    }
    
    {
        const sf::Vector2f cachedPlayerVelocity=world.player.playerVelocity;
        Player& player=world.player;
        player.playerVelocity.y+=world.gravity*clockDeltaSeconds;
        {
            player.playerRect.left+=player.playerVelocity.x*clockDeltaSeconds;
            CollisionResult collisionResult=HandleCollision(player.playerRect,player.playerVelocity,world.level,EOrientation::Horizontal,tileSize);
            if(collisionResult.bisCollided)
            {
                player.playerRect.left=collisionResult.newPosition.x;
            }
        }
        {
            player.playerRect.top-=player.playerVelocity.y*clockDeltaSeconds;
            CollisionResult collisionResult=HandleCollision(player.playerRect,player.playerVelocity,world.level,EOrientation::Vertical,tileSize);
            if(collisionResult.bisCollided)
            {
                player.playerRect.top=collisionResult.newPosition.y;
                if(player.playerVelocity.y<0)
                {
                    player.bIsPlayerOnGround=true;
                }
                player.playerVelocity.y=0.f;
            }
        }

        if (std::abs(player.playerVelocity.x) > 0.0001f)
        {
            player.playerAnimationDirection=player.playerVelocity.x<0? EPlayerDirection::Left:
            EPlayerDirection::Right;
        }

        
        if (player.bIsPlayerOnGround)
        {
            if (std::abs(player.playerVelocity.x) > 0.0001f)
            {
                player.currentAnimation = &player.walkAnimation;
            }
            else
            {
                player.currentAnimation = &player.idleAnimation;
            }
        }
        else
        {
            if (player.playerVelocity.y < 0)
            {
                player.currentAnimation = &player.jumpDownAnimation;
            }
            else
            {
                player.currentAnimation = &player.jumpUpAnimation;
            }
        }
        player.currentAnimation->Update(clockDeltaSeconds);
        for(Enemy&enemy:world.enemies)
        {
            if(!enemy.bDead)
            {
                if(player.playerRect.intersects(enemy.staticObj.rect))
                {
                    if(!player.bIsPlayerOnGround&&player.playerRect.top<enemy.staticObj.rect.top&&cachedPlayerVelocity.y<0)
                    {
                        enemy.bDead=true;
                        player.score+=50;
                        player.playerVelocity.y=player.playerKillEnemyJumpSpeed;
                    }
                    else
                    {
                        world.bGameOver=true;
                        break;
                    }
                }
            }
        }
        for(Coin&coin:world.coins)
        {
            if(!coin.bDead)
            {
                if(player.playerRect.intersects(coin.staticObj.rect))
                {
                    coin.bDead=true;
                    player.score+=100;
                }
            }
        }
    }
    
}

void DrawGame (sf::RenderWindow&window,World&world, const sf::Vector2f&tileSize)
{
    window.clear();
    for (int i = 0; i<world.level.tiles.size(); ++i)
    {   for (int j=0;j<world.level.tiles[i].size();++j)
        {
            const Tile&tile =world.level.tiles[i][j];
            sf::Sprite& sprite=world.level.tileTextureTypeToSprite[tile.textureType];
            sprite.setPosition(tileSize.x*j,tileSize.y*i);
            window.draw(sprite);
        }
    }

    for (Enemy&enemy:world.enemies)
    {
        if(!enemy.bDead)
        {
            enemy.staticObj.spite.setPosition(enemy.staticObj.rect.left,enemy.staticObj.rect.top);
            window.draw(enemy.staticObj.spite);
        }
    }
    for (Coin&coin:world.coins)
    {
        if(!coin.bDead)
        {
            coin.staticObj.spite.setPosition(coin.staticObj.rect.left,coin.staticObj.rect.top);
            window.draw(coin.staticObj.spite);
        }
    }
    Player& player=world.player;

    if (player.currentAnimation!=nullptr)
    {
        player.playerSpite.setTextureRect(player.currentAnimation->GetCurrentFrame());
    }
    const int scaleXSign=player.playerAnimationDirection ==EPlayerDirection::Left?-1.f:1.f;
    const float scaleX=std::abs(player.playerSpite.getScale().x)*scaleXSign;
    player.playerSpite.setScale(scaleX,player.playerSpite.getScale().y);


    const float playerDrawLeftPosition =player.playerRect.left+world.player.playerRect.width/2;
    const float playerDrawTopPosition=player.playerRect.top+world.player.playerRect.height/2;
    
    player.playerSpite.setPosition(playerDrawLeftPosition,playerDrawTopPosition);
    
    window.draw(player.playerSpite);

    world.scoreText.setString("SCORE: "+std::to_string(world.player.score));
    window.draw(world.scoreText);
    
    window.display();
}
