#pragma once

#ifndef ACCOUNT_HPP_
#define ACCOUNT_HPP_

#include "required.h"

class Account : public IScenes {
public:
    Account(std::shared_ptr<sf::RenderWindow>& window, const std::vector<std::string>& lang);
    ~Account();

    void update(sf::Clock& cl, const sf::Time& time, Scenes& currentScene);
    void handleEvent(const sf::Event& event, Scenes& currentScene, sf::Clock& cl, const sf::Time& time);
    void MouseMove_Account(void);
    void MouseClick_Account(Scenes& currentScene);
    void draw();
protected:
private:
    std::shared_ptr<sf::RenderWindow>& _window;
    std::map<std::string, std::unique_ptr<Sprites>> _listSprite;
    sf::Vector2i MousePos;
    sf::FloatRect MouseRect;
    enum Accounts _currentAccount;
};

#endif /* !ACCOUNT_HPP_ */