#pragma once

namespace Warrior {

    struct Stats {
        int x = 6;
        int y = 6;
        int health = 100;
        int healthMax = 100;
        int attack = 10;
        int defense = 5;
        int speed = 5;
        int vision = 6;
    };

    //Stats Player;
    Stats CreateWarrior();
}