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
    SETTINGS,
    DOWNLOADS,
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

enum langue {
    FR,
    EN,
};

#endif /* !REQUIRED_HPP_ */