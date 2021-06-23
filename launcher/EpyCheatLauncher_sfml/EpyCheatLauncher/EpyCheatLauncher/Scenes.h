#pragma once

#ifndef ISCENES_HPP_
#define ISCENES_HPP_

#include "required.h"

class IScenes {
    public:
        virtual ~IScenes() = default;

        virtual void update(sf::Clock &cl, const sf::Time &time, enum Scenes &currentScene) = 0;
        virtual void handleEvent(const sf::Event &event, enum Scenes &currentScene, sf::Clock &cl, const sf::Time &time) = 0;
        virtual void draw() = 0;
    protected:
    private:
};

#endif /* !ISCENES_HPP_ */