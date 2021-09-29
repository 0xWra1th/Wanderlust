#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
class Player{

    public:
        sf::Vector2f position;
        sf::RectangleShape rect;
        sf::RectangleShape feetCollider;
        int speed;
        string name;
        void Move(sf::Vector2f dist);
        void setPosition(sf::Vector2f pos);
        void setTexture(sf::Texture* texture);
        void setSize(sf::Vector2f size);
        void setOrigin(sf::Vector2f origin);
        Player();

};