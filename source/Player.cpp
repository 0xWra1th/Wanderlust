#include <string>
#include <SFML/Graphics.hpp>
#include "Player.h"

Player::Player(){
    // Setup Feet Collider
    feetCollider.setSize(sf::Vector2f(24.f, 5.f));
    feetCollider.setOrigin(sf::Vector2f(12.f, -19.f));
    feetCollider.setPosition(position);
}

void Player::Move(sf::Vector2f dist){
    sf::Vector2f pos = sf::Vector2f(position.x + dist.x, position.y + dist.y);
    position = pos;
    feetCollider.setPosition(position);
    rect.setPosition(pos);
}

void Player::setPosition(sf::Vector2f pos){
    position = pos;
    feetCollider.setPosition(position);
    rect.setPosition(pos);
}

void Player::setTexture(sf::Texture* texture){
    rect.setTexture(texture);
}

void Player::setSize(sf::Vector2f size){
    rect.setSize(size);
}

void Player::setOrigin(sf::Vector2f origin){
    rect.setOrigin(origin);
}