#include "required.h"
#include <Windows.h>

Library::Library(std::shared_ptr<sf::RenderWindow>& window, const std::vector<std::string>& lang) : _window(window)
{
    this->_listSprite["0Background"] = std::make_unique<Sprites>(".\\Ressources\\windows\\main_window.png", sf::Vector2f(0, 0));
    this->_listSprite["Logo"] = std::make_unique<Sprites>(".\\Ressources\\logo\\logo_epycheat.png", sf::Vector2f(82, 76));
    this->_listSprite["Home"] = std::make_unique<Sprites>(".\\Ressources\\home_butt\\home_butt1.png", sf::Vector2f(86, 219));
    this->_listSprite["Shop"] = std::make_unique<Sprites>(".\\Ressources\\shop_butt\\shop_butt1.png", sf::Vector2f(86, 297));
    this->_listSprite["Library"] = std::make_unique<Sprites>(".\\Ressources\\lib_butt\\lib_butt3.png", sf::Vector2f(86, 375));
    this->_listSprite["Tutorial"] = std::make_unique<Sprites>(".\\Ressources\\tuto_butt\\tuto_butt1.png", sf::Vector2f(86, 451));
    this->_listSprite["Downloads"] = std::make_unique<Sprites>(".\\Ressources\\downloads_butt\\downloads_butt1.png", sf::Vector2f(86, 657));
    this->_listSprite["Settings"] = std::make_unique<Sprites>(".\\Ressources\\settings_butt\\settings_butt1.png", sf::Vector2f(86, 733));
    this->_listSprite["Account"] = std::make_unique<Sprites>(".\\Ressources\\account_butt\\account_butt1.png", sf::Vector2f(86, 814));
    this->_listSprite["ScrollBar"] = std::make_unique<Sprites>(".\\Ressources\\scroll_bar\\scroll_bar.png", sf::Vector2f(1543, 43));
    this->_currentLibrary = LIBRARY_BASE;
    this->_window = _window;
}

void Library::update(sf::Clock& cl, const sf::Time& time, Scenes& currentScene)
{
    (void)time;
    (void)cl;
    (void)currentScene;

    this->MousePos = sf::Mouse::getPosition(*this->_window);
    this->MouseRect = sf::FloatRect(float(this->MousePos.x), float(this->MousePos.y), 1, 1);
    this->_listSprite["Home"] = std::make_unique<Sprites>(".\\Ressources\\home_butt\\home_butt1.png", sf::Vector2f(86, 219));
    this->_listSprite["Shop"] = std::make_unique<Sprites>(".\\Ressources\\shop_butt\\shop_butt1.png", sf::Vector2f(86, 297));
    this->_listSprite["Tutorial"] = std::make_unique<Sprites>(".\\Ressources\\tuto_butt\\tuto_butt1.png", sf::Vector2f(86, 451));
    this->_listSprite["Downloads"] = std::make_unique<Sprites>(".\\Ressources\\downloads_butt\\downloads_butt1.png", sf::Vector2f(86, 657));
    this->_listSprite["Settings"] = std::make_unique<Sprites>(".\\Ressources\\settings_butt\\settings_butt1.png", sf::Vector2f(86, 733));
    this->_listSprite["Account"] = std::make_unique<Sprites>(".\\Ressources\\account_butt\\account_butt1.png", sf::Vector2f(86, 814));
    this->_listSprite["ScrollBar"] = std::make_unique<Sprites>(".\\Ressources\\scroll_bar\\scroll_bar.png", sf::Vector2f(1543, 43));
    if (this->_currentLibrary == LIBRARY_HOME) {
        this->_listSprite["Home"] = std::make_unique<Sprites>(".\\Ressources\\home_butt\\home_butt2.png", sf::Vector2f(86, 219));
    }
    if (this->_currentLibrary == LIBRARY_SHOP) {
        this->_listSprite["Shop"] = std::make_unique<Sprites>(".\\Ressources\\shop_butt\\shop_butt2.png", sf::Vector2f(86, 297));
    }
    if (this->_currentLibrary == LIBRARY_TUTORIAL) {
        this->_listSprite["Tutorial"] = std::make_unique<Sprites>(".\\Ressources\\tuto_butt\\tuto_butt2.png", sf::Vector2f(86, 451));
    }
    if (this->_currentLibrary == LIBRARY_DOWNLOADS) {
        this->_listSprite["Downloads"] = std::make_unique<Sprites>(".\\Ressources\\downloads_butt\\downloads_butt2.png", sf::Vector2f(86, 657));
    }
    if (this->_currentLibrary == LIBRARY_SETTINGS) {
        this->_listSprite["Settings"] = std::make_unique<Sprites>(".\\Ressources\\settings_butt\\settings_butt2.png", sf::Vector2f(86, 733));
    }
    if (this->_currentLibrary == LIBRARY_ACCOUNT) {
        this->_listSprite["Account"] = std::make_unique<Sprites>(".\\Ressources\\account_butt\\account_butt2.png", sf::Vector2f(86, 814));
    }
}

void Library::MouseMove_Library(void)
{
    char str[][10] = { ("Home"), ("Shop"), ("Library"), ("Tutorial"), ("Downloads"), ("Settings"), ("Account"), ("ScrollBar"), ("\0") };
    int i = 0;
    sf::FloatRect frect = sf::FloatRect(0, 0, 0, 0);

    for (i; str[i][0] != '\0'; i++) {
        frect.left = float(this->_listSprite[str[i]]->getSprite().getPosition().x);
        frect.top = float(this->_listSprite[str[i]]->getSprite().getPosition().y);
        frect.width = float(this->_listSprite[str[i]]->getSprite().getTextureRect().width);
        frect.height = float(this->_listSprite[str[i]]->getSprite().getTextureRect().height);
        if (frect.intersects(this->MouseRect) == true) {
            this->_currentLibrary = Librarys(i);
            break;
        }
    }
    return;
}

void Library::MouseClick_Library(Scenes& currentScene)
{
    char str[][10] = { ("Home"), ("Shop"), ("Library"), ("Tutorial"), ("Downloads"), ("Settings"), ("Account"), ("ScrollBar"), ("\0") };
    int i = 0;
    sf::FloatRect frect = sf::FloatRect(0, 0, 0, 0);

    for (i; str[i][0] != '\0'; i++) {
        frect.left = float(this->_listSprite[str[i]]->getSprite().getPosition().x);
        frect.top = float(this->_listSprite[str[i]]->getSprite().getPosition().y);
        frect.width = float(this->_listSprite[str[i]]->getSprite().getTextureRect().width);
        frect.height = float(this->_listSprite[str[i]]->getSprite().getTextureRect().height);
        if (frect.intersects(this->MouseRect) == true) {
            currentScene = Scenes(i);
            this->_currentLibrary = LIBRARY_BASE;
            break;
        }
    }
    return;
}

void Library::handleEvent(const sf::Event& event, Scenes& currentScene, sf::Clock& cl, const sf::Time& time)
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
    if (event.type == sf::Event::MouseMoved) {
        this->_currentLibrary = LIBRARY_BASE;
        MouseMove_Library();
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            MouseClick_Library(currentScene);
            std::cerr << "TEST LIBRARY" << std::endl;
        }
    }
}

void Library::draw()
{
    for (auto& val : this->_listSprite) {
        this->_window->draw(val.second->getSprite());
    }
}

Library::~Library()
{
}