//
// Created by desktop on 9/30/24.
//
#include <iostream>

#include "player.h"
#include "utils.h"

#include "game.h"
#include "spawn.h"

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
    std::cout << "3" + stats << " Char stats sent!" << std::endl;
    return "3" + stats;
  }


  void Spawn(Game::State &game, const std::basic_string<char> &characterCreate) {
    game.unitsString += "2";
    // loop through the map x times and lok for 2x2 squares
    // set entities to be in the center of the square
    // I need to send the char and the offset in the map g0317
    auto length = characterCreate.size();

    std::cout << "Crearacter create: " << characterCreate << std::endl;
    std::string name = characterCreate.substr(1, length - 5);
    std::cout << "Name: " << name << std::endl;
    std::string genderStr = characterCreate.substr(length - 4, 1);
    std::cout << "Gender: " << genderStr << std::endl;
    std::string speciesStr = characterCreate.substr(length - 3, 1);
    std::cout << "Species: " << speciesStr << std::endl;
    std::string classStr = characterCreate.substr(length - 2, 1);
    std::cout << "Class: " << classStr << std::endl;
    std::string alignmentStr = characterCreate.substr(length - 1, 1);
    std::cout << "Alignment: " << alignmentStr << std::endl;


    auto gender = (Units::Gender)std::stoi(genderStr);
    auto species = (Units::Species)std::stoi(speciesStr);
    auto unitClass = (Units::Class)std::stoi(classStr);
    auto alignment = (Units::Alignment)std::stoi(alignmentStr);

    Spawn::Add_Unit(game, 6, 6, name, gender, species, unitClass, alignment);
    std::cout << "size: " << game.units.size() << std::endl;
    game.units.at(0).health = 100;
    game.units.at(0).healthMax = 100;
    std::cout << "health: " << game.units.at(0).health << std::endl;

    game.unitsString += (std::to_string(Spawn::Get_Unit_Char(species)) + "0606");
  }

}