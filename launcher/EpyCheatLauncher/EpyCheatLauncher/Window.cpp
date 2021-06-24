#include "required.h"

void Window::_setLang(int lang)
{

}

Window::Window(const size_t &x, const size_t &y)
{
    this->_posX = x;
    this->_posY = y;
    this->View1 = std::make_unique<sf::View>(sf::FloatRect(0, 0, 1589, 868));
    this->_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(this->_posX, this->_posY), "EpyCheat Launcher", sf::Style::Default);
    this->_window->setFramerateLimit(60);
    this->_window->setView(*this->View1);
    this->_window->clear(sf::Color::Black);
    this->_currentScene = HOME;
    this->_setLang(1);
    this->_sceneManager[HOME] = std::make_unique<Home>(this->_window, this->_langLauncher);
    //this->_sceneManager[(Scenes)STORE] = std::make_unique<Home>(this->_window);
    //this->_sceneManager[(Scenes)SHOP] = std::make_unique<Shop>(this->_window, this->_langLauncher);
}

void Window::coreLoop()
{
    while (this->_window->isOpen()) {
        this->time = this->cl.getElapsedTime();
        while (this->_window->pollEvent(this->_event)) {
            this->_sceneManager[this->_currentScene]->handleEvent(this->_event, this->_currentScene, this->cl, this->time);
        }
        this->_sceneManager[this->_currentScene]->update(this->cl, this->time, this->_currentScene);
        this->_window->clear(sf::Color::Magenta);
        this->_sceneManager[this->_currentScene]->draw();
        this->_window->display();
    }
}

Window::~Window()
{

}