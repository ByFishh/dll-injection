#pragma once

#ifndef DL_HPP_
#define DL_HPP_

#include "required.h"

class Download : public IScenes {
    public:
        Download(std::shared_ptr<sf::RenderWindow>& window, const std::vector<std::string>& lang);
        ~Download();

        void update(sf::Clock& cl, const sf::Time& time, Scenes& currentScene);
        void handleEvent(const sf::Event& event, Scenes& currentScene, sf::Clock& cl, const sf::Time& time);
        void MouseMove_Download(void);
        void MouseClick_Download(Scenes& currentScene);
        void draw();
    protected:
    private:
        std::shared_ptr<sf::RenderWindow>& _window;
        std::map<std::string, std::unique_ptr<Sprites>> _listSprite;
        sf::Vector2i MousePos;
        sf::FloatRect MouseRect;
        enum Downloads _currentDownload;
};

#endif /* !DL_HPP_ */