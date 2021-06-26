#pragma once

#ifndef LIB_HPP_
#define LIB_HPP_

#include "required.h"

class Library : public IScenes {
    public:
        Library(std::shared_ptr<sf::RenderWindow>& window, const std::vector<std::string>& lang);
        ~Library();

        void update(sf::Clock& cl, const sf::Time& time, Scenes& currentScene);
        void handleEvent(const sf::Event& event, Scenes& currentScene, sf::Clock& cl, const sf::Time& time);
        void MouseMove_Library(void);
        void MouseClick_Library(Scenes& currentScene);
        void draw();
    protected:
    private:
        std::shared_ptr<sf::RenderWindow>& _window;
        std::map<std::string, std::unique_ptr<Sprites>> _listSprite;
        sf::Vector2i MousePos;
        sf::FloatRect MouseRect;
        enum Librarys _currentLibrary;
};

#endif /* !LIB_HPP_ */