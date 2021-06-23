#include "required.h"
#include <Windows.h>
#include <chrono>
#include <thread>

Home::Home(std::shared_ptr<sf::RenderWindow>& window, const std::vector<std::string>& lang) : _window(window)
{
    std::cerr << "TEST HOME" << std::endl;
    this->_listSprite["0Background"] = std::make_unique<Sprites>(".\\Ressources\\windows\\main_window.png", sf::Vector2f(0, 0));
    this->_listSprite["Logo"] = std::make_unique<Sprites>(".\\Ressources\\logo\\logo_epycheat.png", sf::Vector2f(82, 76));
    this->_listSprite["Home"] = std::make_unique<Sprites>(".\\Ressources\\home_butt\\home_butt3.png", sf::Vector2f(86, 219));
    this->_listSprite["Shop"] = std::make_unique<Sprites>(".\\Ressources\\shop_butt\\shop_butt2.png", sf::Vector2f(86, 297));
    this->_listSprite["Library"] = std::make_unique<Sprites>(".\\Ressources\\lib_butt\\lib_butt1.png", sf::Vector2f(86, 375));
    this->_listSprite["Tutorial"] = std::make_unique<Sprites>(".\\Ressources\\tuto_butt\\tuto_butt1.png", sf::Vector2f(86, 451));
    this->_listSprite["Downloads"] = std::make_unique<Sprites>(".\\Ressources\\downloads_butt\\downloads_butt1.png", sf::Vector2f(86, 657));
    this->_listSprite["Settings"] = std::make_unique<Sprites>(".\\Ressources\\settings_butt\\settings_butt1.png", sf::Vector2f(86, 733));
    this->_listSprite["Account"] = std::make_unique<Sprites>(".\\Ressources\\account_butt\\account_butt1.png", sf::Vector2f(86, 814));
    this->_listSprite["ScrollBar"] = std::make_unique<Sprites>(".\\Ressources\\scroll_bar\\scroll_bar.png", sf::Vector2f(1543, 43));
    //std::chrono::milliseconds timespan(111605); // or whatever
    //std::this_thread::sleep_for(timespan);
    //this->_listSprite["nFront"] = std::make_unique<Sprites>("assets/images/backmain.png", sf::Vector2f(525, 50));
}

void Home::update(sf::Clock& cl, const sf::Time& time, Scenes& currentScene)
{
    (void)time;
    (void)cl;
    (void)currentScene;
    this->MousePos = sf::Mouse::getPosition();
    /*if (this->_listText["play"]->getText().getGlobalBounds().contains(static_cast<sf::Vector2f>(this->MousePos))) {
        this->_listText["play"]->getText().setFillColor(sf::Color::Green);
    }
    else {
        this->_listText["play"]->getText().setFillColor(sf::Color::White);
    }
    if (this->_listText["quit"]->getText().getGlobalBounds().contains(static_cast<sf::Vector2f>(this->MousePos))) {
        this->_listText["quit"]->getText().setFillColor(sf::Color::Green);
    }
    else {
        this->_listText["quit"]->getText().setFillColor(sf::Color::White);
    }*/
}

void Home::handleEvent(const sf::Event& event, Scenes& currentScene, sf::Clock& cl, const sf::Time& time)
{
    (void)time;
    (void)cl;

    if (event.type == sf::Event::Closed) {
        this->_window->close();
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            this->_window->close();
        }
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            /*if (this->_listText["play"]->getText().getGlobalBounds().contains(static_cast<sf::Vector2f>(this->MousePos))) {
                this->_listSound["menuMusic"]->getMusic().stop();
                currentScene = GAME;
            }
            if (this->_listText["quit"]->getText().getGlobalBounds().contains(static_cast<sf::Vector2f>(this->MousePos))) {
                this->_window->close();
            }*/
        }
    }
}

void Home::draw()
{
    for (auto& val : this->_listSprite) {
        this->_window->draw(val.second->getSprite());
    }
    /*for (auto& val : this->_listText) {
        this->_window->draw(val.second->getText());
    }*/
}

Home::~Home()
{
}