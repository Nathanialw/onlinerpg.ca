//
// Created by desktop on 9/30/24.
//
#include <iostream>

#include "player.h"
#include "utils.h"

#include "game.h"
//#include "units.h"

namespace Player {

//  Units::Unit Get(Game::State &game) {
//    return game.units[0];
//  }

  std::string Get_Stats(Game::State &game) {
    //only append with what is being updated
    //when the stat IS updated on then add it to the string

    //prepend with 0000 to tell which stats are being sent
    //name + gender + species + class + alignment

    auto &player = game.Get_Player();

    auto health = Utils::Prepend_Zero_3Digit(player.health) + Utils::Prepend_Zero_3Digit(player.healthMax);
    auto speed = std::to_string(player.speed) + std::to_string(player.maxSpeed);
    auto damage = Utils::Prepend_Zero(player.minDamage) + Utils::Prepend_Zero(player.maxDamage);
    auto variableStats = player.potrait + Utils::Prepend_Zero(player.AC) + Utils::Prepend_Zero_3Digit(player.age) + health + speed + damage;

    //    2 + 3 + 3 + 3 + 1 + 1 + 2 + 2

    std::string stats = "1111" + player.name + variableStats + std::to_string((int)player.def.gender) + std::to_string((int)player.def.species) + std::to_string((int)player.def.unitClass) + std::to_string((int)player.def.alignment);
    std::cout << "3" + stats << std::endl;
    return "3" + stats;
  }

}