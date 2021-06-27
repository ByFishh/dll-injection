#include "required.h"

Sprites::Sprites(const std::string &path, const sf::Vector2f &pos)
{
    if (!this->_text.loadFromFile(path)) {
        exit(84);
    }
    this->_sprite.setTexture(this->_text);
    this->_sprite.setPosition(pos);
}

Sprites::Sprites(const std::string &path, const sf::Vector2f &pos, const sf::IntRect &rct)
{
    if (!this->_text.loadFromFile(path)) {
        exit(84);
    }
    this->_sprite.setTexture(this->_text);
    this->_sprite.setTextureRect(rct);
    this->_sprite.setPosition(pos);
}

Sprites::Sprites(const Sprites &cpy)
{
    this->_text = cpy._text;
    this->_sprite = cpy._sprite;
}

Sprites &Sprites::operator=(const Sprites &cpy)
{
    this->_text = cpy._text;
    this->_sprite = cpy._sprite;
    return (*this);
}

sf::Sprite &Sprites::getSprite()
{
    return (this->_sprite);
}

Sprites::~Sprites()
{

}