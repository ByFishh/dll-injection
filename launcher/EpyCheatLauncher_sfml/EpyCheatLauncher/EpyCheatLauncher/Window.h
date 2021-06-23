#pragma once

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "required.h"

class Window {
    public:
        Window(const size_t &x, const size_t &y);
        void coreLoop();
        ~Window();

    protected:
    private:
        void _setLang(int lang);

        std::shared_ptr<sf::RenderWindow> _window;
        sf::Event _event;
        std::map<enum Scenes, std::unique_ptr<IScenes>> _sceneManager;
        enum Scenes _currentScene;
        std::unique_ptr<sf::View> View1;
        size_t _posX;
        size_t _posY;
        sf::Clock cl;
        sf::Time time;
        std::vector<std::string> _langLauncher;
};

#endif /* !WINDOW_HPP_ */
