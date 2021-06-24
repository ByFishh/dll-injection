#pragma once

#ifndef SPRITES_HPP_
#define SPRITES_HPP_

#include "required.h"

class Sprites
{
    public:
        Sprites(const std::string &path, const sf::Vector2f &pos);
        Sprites(const std::string &path, const sf::Vector2f &pos, const sf::IntRect &rct);
        Sprites(const Sprites &cpy);
        Sprites &operator=(const Sprites &cpy);
        sf::Sprite &getSprite();
        ~Sprites();

    protected:
    private:
        sf::Texture _text;
        sf::Sprite _sprite;
};

#endif /* !SPRITES_HPP_ */