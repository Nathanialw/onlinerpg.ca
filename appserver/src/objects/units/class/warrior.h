#pragma once
#include <cstdint>

namespace Warrior {

    struct Stats {
        uint8_t x = 6;
        uint8_t y = 6;
        uint8_t health = 100;
        uint8_t healthMax = 100;
        uint8_t attack = 10;
        uint8_t defense = 5;
        uint8_t speed = 5;
        uint8_t vision = 6;
    };

    //Stats Player;
    Stats CreateWarrior();
}