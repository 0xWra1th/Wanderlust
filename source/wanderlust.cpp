// A small 2.5D game where you can run around a world.

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cmath>

#include "Player.h"

#define LOG(x) std::cout << x << std::endl;

int main()
{
    // -------------- SETUP --------------
    // Window
    sf::RenderWindow window(sf::VideoMode(960, 960), "Wanderlust", sf::Style::Close);
    window.setFramerateLimit(60);

    // Clock
    sf::Clock deltaTime;
    
    // RNG
    srand((unsigned) time(0));

    // Variables
    sf::Vector2f center = sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f);
    
    // -----------------------------------

    // ----------- TEXTURES --------------
    std::string spritesheet = "../assets/Kenny/Spritesheet/roguelikeSheet_transparent.png";
    std::string character = "../assets/Hero.png";

    sf::Texture playerUp;
    playerUp.loadFromFile(character, sf::IntRect(sf::Vector2i(0 * 16, 0 * 16), sf::Vector2i(16, 16)));

    sf::Texture playerDown;
    playerDown.loadFromFile(character, sf::IntRect(sf::Vector2i(4 * 16, 0 * 16), sf::Vector2i(16, 16)));

    sf::Texture playerLeft;
    playerLeft.loadFromFile(character, sf::IntRect(sf::Vector2i(0 * 16, 1 * 16), sf::Vector2i(16, 16)));

    sf::Texture playerRight;
    playerRight.loadFromFile(character, sf::IntRect(sf::Vector2i(7 * 16, 1 * 16), sf::Vector2i(16, 16)));

    sf::Texture grassTile1;
    grassTile1.loadFromFile(spritesheet, sf::IntRect(sf::Vector2i((5 * 16) + 5 , (0 * 16) + 0), sf::Vector2i(16, 16)));
    
    sf::Texture grassTile2;
    grassTile2.loadFromFile(spritesheet, sf::IntRect(sf::Vector2i((5 * 16) + 5 , (1 * 16) + 1), sf::Vector2i(16, 16)));
    
    sf::Texture waterTile1;
    waterTile1.loadFromFile(spritesheet, sf::IntRect(sf::Vector2i((0 * 16) + 0 , (0 * 16) + 0), sf::Vector2i(16, 16)));
    
    sf::Texture waterTile2;
    waterTile2.loadFromFile(spritesheet, sf::IntRect(sf::Vector2i((1 * 16) + 1 , (0 * 16) + 0), sf::Vector2i(16, 16)));
    
    sf::Texture dirtTile1;
    dirtTile1.loadFromFile(spritesheet, sf::IntRect(sf::Vector2i((6 * 16) + 6 , (0 * 16) + 0), sf::Vector2i(16, 16)));
    
    sf::Texture dirtTile2;
    dirtTile2.loadFromFile(spritesheet, sf::IntRect(sf::Vector2i((6 * 16) + 6 , (1 * 16) + 1), sf::Vector2i(16, 16)));
    
    sf::Texture stoneTile1;
    stoneTile1.loadFromFile(spritesheet, sf::IntRect(sf::Vector2i((6 * 16) + 6 , (2 * 16) + 2), sf::Vector2i(16, 16)));
    
    sf::Texture stoneTile2;
    stoneTile2.loadFromFile(spritesheet, sf::IntRect(sf::Vector2i((6 * 16) + 6 , (3 * 16) + 3), sf::Vector2i(16, 16)));
    
    sf::Texture tentTile1;
    tentTile1.loadFromFile(spritesheet, sf::IntRect(sf::Vector2i((46 * 16) + 46 , (10 * 16) + 10), sf::Vector2i(16, 16)));
    
    sf::Texture tentTile2;
    tentTile2.loadFromFile(spritesheet, sf::IntRect(sf::Vector2i((47 * 16) + 47 , (10 * 16) + 10), sf::Vector2i(16, 16)));
    
    sf::Texture tentTile3;
    tentTile3.loadFromFile(spritesheet, sf::IntRect(sf::Vector2i((46 * 16) + 46 , (11 * 16) + 11), sf::Vector2i(16, 16)));
    
    sf::Texture tentTile4;
    tentTile4.loadFromFile(spritesheet, sf::IntRect(sf::Vector2i((47 * 16) + 47 , (11 * 16) + 11), sf::Vector2i(16, 16)));
    
    sf::Texture campfireTile;
    campfireTile.loadFromFile(spritesheet, sf::IntRect(sf::Vector2i((15 * 16) + 15 , (8 * 16) + 8), sf::Vector2i(16, 16)));
    
    // -----------------------------------

    // ------------ OBJECTS --------------
    Player player;
    player.rect = sf::RectangleShape(sf::Vector2f(48.f, 48.f));
    player.setOrigin(sf::Vector2f(player.rect.getSize().x / 2.f, player.rect.getSize().y / 2.f));
    player.setTexture(&playerDown);
    player.speed = 2;
    player.setPosition(center);
    player.name = "Daniel";
    // -----------------------------------
    
    // ---------- GENERATE MAP -----------
    // COUNT
    fstream mapFile("../maps/village/map_01.txt");
    std::string token;
    int numTiles = 0;
    while (getline (mapFile, token, ' ')) {
        if(token != "\n"){
            numTiles+=1;
        }
    }
    mapFile.close();

    // Create Tiles
    int startRow = 0;
    int startCol = 0;
    int rows = sqrt(numTiles); // MAP WILL ALWAYS BE A SQUARE
    int cols = sqrt(numTiles);
    int tileOffsetX = ( cols * 24 ) * startCol;
    int tileOffsetY = ( rows * 24 ) * startRow;
    sf::RectangleShape Tiles[numTiles];
    int tileCounter = 0;
    int r = 0;
    int c = 0;

    mapFile.open("../maps/village/map_01.txt");
    while (getline (mapFile, token, ' ')) {
        if(token != "\n"){
            Tiles[tileCounter].setSize(sf::Vector2f( 48.f, 48.f ));
            Tiles[tileCounter].setOrigin(sf::Vector2f( 0.f, 0.f ));
            Tiles[tileCounter].setPosition(sf::Vector2f(( c * 48.f )-tileOffsetX, ( r * 48.f )-tileOffsetY));
            int randNum = (rand() % 2 ) + 1;
            if(token == "G"){  
                if(randNum == 1){
                    Tiles[tileCounter].setTexture(&grassTile1);
                }else if(randNum == 2){
                    Tiles[tileCounter].setTexture(&grassTile2);
                }
            }else if(token == "D"){
                if(randNum == 1){
                    Tiles[tileCounter].setTexture(&dirtTile1);
                }else if(randNum == 2){
                    Tiles[tileCounter].setTexture(&dirtTile2);
                }
            }else if(token == "W"){
                if(randNum == 1){
                    Tiles[tileCounter].setTexture(&waterTile1);
                }else if(randNum == 2){
                    Tiles[tileCounter].setTexture(&waterTile2);
                }
            }else if(token == "S"){
                if(randNum == 1){
                    Tiles[tileCounter].setTexture(&stoneTile1);
                }else if(randNum == 2){
                    Tiles[tileCounter].setTexture(&stoneTile2);
                }
            }else if(token == "0"){
                Tiles[tileCounter].setTexture(&tentTile1); 
            }else if(token == "1"){
               Tiles[tileCounter].setTexture(&tentTile2); 
            }else if(token == "2"){
                Tiles[tileCounter].setTexture(&tentTile3); 
            }else if(token == "3"){
                Tiles[tileCounter].setTexture(&tentTile4); 
            }else if(token == "F"){
                Tiles[tileCounter].setTexture(&campfireTile);
            }

            tileCounter = tileCounter + 1;
            c = c + 1;
        }else{
            //if(tileCounter != 0){
                c = 0;
                r++;
            //}
        }
    }
    mapFile.close();
    // -----------------------------------

    // ------------ SHADERS --------------
    if (!sf::Shader::isAvailable())
    {
        LOG("ERR: Shaders not supported!");
    }

    sf::Shader shader;
    if (!shader.loadFromFile("../shaders/vertex-shader.glsl", "../shaders/fragment-shader.glsl"))
    {
        LOG("ERR: Failed to load shaders!");
    }

    shader.setUniform("texture", sf::Shader::CurrentTexture);
    // -----------------------------------

    // ------------ GAME LOOP ------------
    while (window.isOpen())
    {   
        // Tick Clock
        sf::Time dt = deltaTime.restart();

        // ---------- HANDLE EVENTS ----------
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }else if (event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape){
                    window.close();
                    return 0;
                }
            }
        }
        // -----------------------------------

        // ------------ CONTROLS -------------
        // Up & Down
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            player.Move(sf::Vector2f(0.f, -player.speed * dt.asSeconds() * 100.f));
            player.setTexture(&playerUp);
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            player.Move(sf::Vector2f(0.f, player.speed * dt.asSeconds() * 100.f));
            player.setTexture(&playerDown);
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            player.Move(sf::Vector2f(-player.speed * dt.asSeconds() * 100.f, 0.f));
            player.setTexture(&playerLeft);
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            player.Move(sf::Vector2f(player.speed * dt.asSeconds() * 100.f, 0.f));
            player.setTexture(&playerRight);
        }
        // -----------------------------------

        // ------------ COLLISONS ------------
        for(int i=0;i<numTiles;i++){
            if(Tiles[i].getTexture() == &waterTile1 || Tiles[i].getTexture() == &waterTile2){
                if(player.feetCollider.getGlobalBounds().intersects(Tiles[i].getGlobalBounds())){
                    if(player.position.x < Tiles[i].getPosition().x){
                        player.setPosition(sf::Vector2f(Tiles[i].getPosition().x - 12.f, player.position.y));
                    }else if(player.position.x > Tiles[i].getPosition().x + 48.f){
                        player.setPosition(sf::Vector2f(Tiles[i].getPosition().x + 60.f, player.position.y));
                    }else if(player.position.y < Tiles[i].getPosition().y){
                        player.setPosition(sf::Vector2f(player.position.x, Tiles[i].getPosition().y - 24.f));
                    }else if(player.position.y > Tiles[i].getPosition().y + 19.f){
                        player.setPosition(sf::Vector2f(player.position.x, Tiles[i].getPosition().y + 29.f));
                    }
                }
            }
        }
        // -----------------------------------

        // ----------- MOVE SCENES -----------
        if( player.position.x > window.getSize().x){
            player.position.x -= window.getSize().x;
            for(int i=0;i<numTiles;i++){
                Tiles[i].setPosition(Tiles[i].getPosition().x - window.getSize().x, Tiles[i].getPosition().y);
            }
        }else if( player.position.x < 0){
            player.position.x += window.getSize().x;
            for(int i=0;i<numTiles;i++){
                Tiles[i].setPosition(Tiles[i].getPosition().x + window.getSize().x, Tiles[i].getPosition().y);
            }
        }else if( player.position.y > window.getSize().y){
            player.position.y -= window.getSize().y;
            for(int i=0;i<numTiles;i++){
                Tiles[i].setPosition(Tiles[i].getPosition().x, Tiles[i].getPosition().y - window.getSize().y);
            }
        }else if( player.position.y < 0){
            player.position.y += window.getSize().y;
            for(int i=0;i<numTiles;i++){
                Tiles[i].setPosition(Tiles[i].getPosition().x, Tiles[i].getPosition().y + window.getSize().y);
            }
        }
        // -----------------------------------

        // ---------- UPDATE WINDOW ----------
        window.clear();

        for(int i=0;i<numTiles;i++){
            window.draw(Tiles[i], &shader);
        }

        window.draw(player.rect, &shader);
        
        window.display();
        // -----------------------------------
    }
    // -----------------------------------

    return 0;
}
