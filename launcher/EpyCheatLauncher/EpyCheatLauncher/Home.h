#pragma once

#ifndef HOME_HPP_
#define HOME_HPP_

#include "required.h"

class Home : public IScenes {
    public:
        Home(std::shared_ptr<sf::RenderWindow> &window, const std::vector<std::string> &lang);
        ~Home();

        void update(sf::Clock &cl, const sf::Time &time, Scenes &currentScene);
        void handleEvent(const sf::Event &event, Scenes &currentScene, sf::Clock &cl, const sf::Time &time);
        void MouseMove_Home(void);
        void MouseClick_Home(Scenes &currentScene);
        void draw();
    protected:
    private:
        std::shared_ptr<sf::RenderWindow> &_window;
        std::map<std::string, std::unique_ptr<Sprites>> _listSprite;
        sf::Vector2i MousePos;
        sf::FloatRect MouseRect;
        enum Homes _currentHome;
};

#endif /* !HOME_HPP_ */