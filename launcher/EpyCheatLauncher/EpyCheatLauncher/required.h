#pragma once

#ifndef REQUIRED_HPP_
#define REQUIRED_HPP_

#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <fstream>
#include <Windows.h>
#include "Scenes.h"
#include "Window.h"
#include "Sprites.h"
#include "Shop.h"
#include "Library.h"
#include "Tutorial.h"
#include "Downloads.h"
#include "Settings.h"
#include "Account.h"
#include "Home.h"

static const std::pair<std::string, std::string> tab_menu[] = {
    std::make_pair("NYIA", "NYIA"),
    std::make_pair("PLAY", "LANCER"),
    std::make_pair("QUIT", "QUITTER"),
};

enum Scenes {
    HOME,
    SHOP,
    LIBRARY,
    TUTORIAL,
    DOWNLOADS,
    SETTINGS,
    ACCOUNT,
};

enum Homes {
    HOME_BASE,
    HOME_SHOP,
    HOME_LIBRARY,
    HOME_TUTORIAL,
    HOME_DOWNLOADS,
    HOME_SETTINGS,
    HOME_ACCOUNT,
};

enum Shops {
    SHOP_HOME,
    SHOP_BASE,
    SHOP_LIBRARY,
    SHOP_TUTORIAL,
    SHOP_DOWNLOADS,
    SHOP_SETTINGS,
    SHOP_ACCOUNT,
};

enum Librarys {
    LIBRARY_HOME,
    LIBRARY_SHOP,
    LIBRARY_BASE,
    LIBRARY_TUTORIAL,
    LIBRARY_DOWNLOADS,
    LIBRARY_SETTINGS,
    LIBRARY_ACCOUNT,
};

enum Tutorials {
    TUTO_HOME,
    TUTO_SHOP,
    TUTO_LIBRARY,
    TUTO_BASE,
    TUTO_DOWNLOADS,
    TUTO_SETTINGS,
    TUTO_ACCOUNT,
};

enum Downloads {
    DL_HOME,
    DL_SHOP,
    DL_LIBRARY,
    DL_TUTORIAL,
    DL_BASE,
    DL_SETTINGS,
    DL_ACCOUNT,
};

enum Settings {
    SETTING_HOME,
    SETTING_SHOP,
    SETTING_LIBRARY,
    SETTING_TUTORIAL,
    SETTING_DOWNLOADS,
    SETTING_BASE,
    SETTING_ACCOUNT,
};

enum Accounts {
    ACCOUNT_HOME,
    ACCOUNT_SHOP,
    ACCOUNT_LIBRARY,
    ACCOUNT_TUTORIAL,
    ACCOUNT_DOWNLOADS,
    ACCOUNT_SETTINGS,
    ACCOUNT_BASE,
};

enum langue {
    FR,
    EN,
};

#endif /* !REQUIRED_HPP_ */