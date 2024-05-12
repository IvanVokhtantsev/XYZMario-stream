#include <regex>

#include "GameLogic.h"


int main()
{
    const sf::Vector2i textureTileSize(16,16);
    const sf::Vector2f drawScale(3.f, 3.f);
    const sf::Vector2f tileSize(textureTileSize.x*drawScale.x, textureTileSize.y*drawScale.y);
    
    sf::RenderWindow window(sf::VideoMode(16 * tileSize.x, 12 * tileSize.y), "Mario");
    
    sf::Texture tileSetTexture;
    tileSetTexture.loadFromFile("Resources/TileSet.png");

    LevelDescriptor levelDescriptor;
    levelDescriptor.levelSymbols=
    {
        /* 0*/{'B','S','S','S','S','S','S','S','S','S','S','S','S','S','S','B'},
        /* 1*/{'B','S','S','S','S','S','S','S','S','S','S','S','S','S','S','B'},
        /* 2*/{'B','S','S','S','S','S','S','S','S','S','S','S','S','S','S','B'},
        /* 3*/{'B','S','S','S','S','S','S','S','S','S','S','S','S','S','S','B'},
        /* 4*/{'B','S','S','S','S','S','S','S','S','S','S','S','S','S','S','B'},
        /* 5*/{'B','S','S','S','S','S','S','S','S','S','S','S','S','S','S','B'},
        /* 6*/{'B','S','S','S','S','S','S','S','S','S','S','S','S','S','S','B'},
        /* 7*/{'B','S','S','S','S','S','S','B','B','S','S','S','S','S','S','B'},
        /* 8*/{'B','S','S','S','S','S','S','S','S','S','S','S','S','S','S','B'},
        /* 9*/{'B','S','S','S','B','S','S','S','S','S','S','S','S','S','S','B'},
        /*10*/{'B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B'},
        /*11*/{'B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B'}
    };
    levelDescriptor.tileSetTexture=tileSetTexture;
    levelDescriptor.tileTextureTypeToTextureRect[ETileTexture::Empty]=sf::IntRect(274,365,textureTileSize.x,textureTileSize.y);
    levelDescriptor.tileTextureTypeToTextureRect[ETileTexture::Ground]=sf::IntRect(373,102,textureTileSize.x,textureTileSize.y);
    sf::Font font;
    font.loadFromFile("Resources/DefaultFont.ttf");

    while (window.isOpen())
    {
        World world;

        world.scoreText.setFont(font);
        world.scoreText.setCharacterSize(18);
        world.scoreText.setPosition(tileSize.x,  0.f);
        world.scoreText.setFillColor(sf::Color::White);
        world.scoreText.setStyle(sf::Text::Style::Bold);
        
        world.level=CreateLevel(levelDescriptor,drawScale);
    
        {
            world.player.playerSpite.setTexture(tileSetTexture);
            world.player.playerSpite.setTextureRect(sf::IntRect(117,507,textureTileSize.x,textureTileSize.y));
            world.player.playerSpite.setScale(drawScale);
            world.player.playerRect=sf::FloatRect(tileSize.x*1,tileSize.y*9,tileSize.x,tileSize.y);
            world.player.playerSpite.setOrigin(textureTileSize.x/2.f,textureTileSize.y/2.f);

            {
                world.player.walkAnimation.texture=tileSetTexture;
                world.player.walkAnimation.speed=7.f;
                world.player.walkAnimation.frames.push_back(sf::IntRect(84,507,
                    textureTileSize.x,textureTileSize.y));
                world.player.walkAnimation.frames.push_back(sf::IntRect(99,507,
                    textureTileSize.x,textureTileSize.y));
                world.player.walkAnimation.frames.push_back(sf::IntRect(117,507,
                    textureTileSize.x,textureTileSize.y));
            }

            {
                world.player.idleAnimation.texture=tileSetTexture;
                world.player.idleAnimation.speed=0.f;
                world.player.idleAnimation.frames.push_back(sf::IntRect(23,507,
                    textureTileSize.x,textureTileSize.y));
            }
            
            {
                world.player.jumpUpAnimation.texture=tileSetTexture;
                world.player.jumpUpAnimation.speed=1.f;
                world.player.jumpUpAnimation.frames.push_back(sf::IntRect(139,507,
                    textureTileSize.x,textureTileSize.y));
            }
            {
                world.player.jumpDownAnimation.texture=tileSetTexture;
                world.player.jumpDownAnimation.speed=7.f;
                world.player.jumpDownAnimation.frames.push_back(sf::IntRect(68,528,
                    textureTileSize.x,textureTileSize.y));
                world.player.jumpDownAnimation.frames.push_back(sf::IntRect(90,528,
                    textureTileSize.x,textureTileSize.y));
                world.player.jumpDownAnimation.frames.push_back(sf::IntRect(113,528,
                    textureTileSize.x,textureTileSize.y));
            }
            
        }
        
    
        {
            Enemy enemy;
            enemy.staticObj.spite.setTexture(tileSetTexture);
            enemy.staticObj.spite.setTextureRect(sf::IntRect(187,894,textureTileSize.x,textureTileSize.y));
            enemy.staticObj.spite.setScale(drawScale);
            enemy.staticObj.rect=sf::FloatRect(tileSize.x*7,tileSize.y*9,tileSize.x,tileSize.y);
            enemy.enemySpeed=150.f;
            enemy.enemyVelocity.x=-enemy.enemySpeed;
            world.enemies.push_back(enemy);
        }

        {
            Coin coin;
            sf::Vector2i coinTextureSize(10,14);
            coin.staticObj.spite.setTexture(tileSetTexture);
            coin.staticObj.spite.setTextureRect(sf::IntRect(427,163,coinTextureSize.x,coinTextureSize.y));
            coin.staticObj.spite.setScale(drawScale);
            coin.staticObj.rect=sf::FloatRect(tileSize.x*8,tileSize.y*6,coinTextureSize.x*drawScale.x,coinTextureSize.y*drawScale.y);
            world.coins.push_back(coin);
        }
    
    
    
        sf::Clock clock;
    
        while (!world.bGameOver&&window.isOpen())
        {
            sf::sleep(sf::seconds(0.001f));
            float clockDeltaSeconds=clock.getElapsedTime().asSeconds();
            clock.restart();
        
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                HandleWindowsEvent(event,world.player);
            }
        
            HandleInput(world.player);
        
            UpdateGame(world, clockDeltaSeconds,tileSize);

            DrawGame(window,world,tileSize);
        }
    }
    return 0;
}