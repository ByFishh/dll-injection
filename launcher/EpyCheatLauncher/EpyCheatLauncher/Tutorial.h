#pragma once

#ifndef TUTO_HPP_
#define TUTO_HPP_

#include "required.h"

class Tutorial : public IScenes {
public:
    Tutorial(std::shared_ptr<sf::RenderWindow>& window, const std::vector<std::string>& lang);
    ~Tutorial();

    void update(sf::Clock& cl, const sf::Time& time, Scenes& currentScene);
    void handleEvent(const sf::Event& event, Scenes& currentScene, sf::Clock& cl, const sf::Time& time);
    void MouseMove_Tutorial(void);
    void MouseClick_Tutorial(Scenes& currentScene);
    void draw();
protected:
private:
    std::shared_ptr<sf::RenderWindow>& _window;
    std::map<std::string, std::unique_ptr<Sprites>> _listSprite;
    sf::Vector2i MousePos;
    sf::FloatRect MouseRect;
    enum Tutorials _currentTutorial;
};

#endif /* !TUTO_HPP_ */