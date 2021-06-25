#pragma once

#ifndef SHOP_HPP_
#define SHOP_HPP_

#include "required.h"

class Shop : public IScenes {
    public:
        Shop(std::shared_ptr<sf::RenderWindow>& window, const std::vector<std::string>& lang);
        ~Shop();

        void update(sf::Clock& cl, const sf::Time& time, Scenes& currentScene);
        void handleEvent(const sf::Event& event, Scenes& currentScene, sf::Clock& cl, const sf::Time& time);
        void MouseMove_Shop(void);
        void MouseClick_Shop(Scenes& currentScene);
        void draw();
    protected:
    private:
        std::shared_ptr<sf::RenderWindow>& _window;
        std::map<std::string, std::unique_ptr<Sprites>> _listSprite;
        sf::Vector2i MousePos;
        sf::FloatRect MouseRect;
        enum Shops _currentShop;
};

#endif /* !SHOP_HPP_ */