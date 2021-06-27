#pragma once

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include "required.h"

class Setting : public IScenes {
public:
    Setting(std::shared_ptr<sf::RenderWindow>& window, const std::vector<std::string>& lang);
    ~Setting();

    void update(sf::Clock& cl, const sf::Time& time, Scenes& currentScene);
    void handleEvent(const sf::Event& event, Scenes& currentScene, sf::Clock& cl, const sf::Time& time);
    void MouseMove_Setting(void);
    void MouseClick_Setting(Scenes& currentScene);
    void draw();
protected:
private:
    std::shared_ptr<sf::RenderWindow>& _window;
    std::map<std::string, std::unique_ptr<Sprites>> _listSprite;
    sf::Vector2i MousePos;
    sf::FloatRect MouseRect;
    enum Settings _currentSetting;
};

#endif /* !SETTINGS_HPP_ */