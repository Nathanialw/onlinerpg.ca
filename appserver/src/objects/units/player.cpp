//
// Created by desktop on 9/30/24.
//
#include <iostream>

#include "player.h"
#include "utils.h"

#include "game.h"
#include "spawn.h"

namespace Player {

//  Units::Unit Get(Game::Instance &game) {
//    return game.units[0];
//  }

  std::string Get_Stats(Game::Instance &game) {
    std::cout << "sending char stats back  to client" << std::endl;

    //only append with what is being updated
    //when the stat IS updated on then add it to the string

    //prepend with 0000 to tell which stats are being sent
    //name + gender + species + class + alignment


    auto health = Utils::Prepend_Zero_3Digit(game.Get_Player().health) + Utils::Prepend_Zero_3Digit(game.Get_Player().healthMax);
    auto speed = std::to_string(game.Get_Player().speed) + std::to_string(game.Get_Player().maxSpeed);
    auto damage = Utils::Prepend_Zero(game.Get_Player().minDamage) + Utils::Prepend_Zero(game.Get_Player().maxDamage);
    auto variableStats = "001" + Utils::Prepend_Zero(game.Get_Player().AC) + Utils::Prepend_Zero_3Digit(game.Get_Player().age) + health + speed + damage;
//    auto variableStats = Utils::Prepend_Zero(game.Get_Player().AC) + Utils::Prepend_Zero_3Digit(game.Get_Player().age) + health + speed + damage;

    //    2 + 3 + 3 + 3 + 1 + 1 + 2 + 2

    std::string stats = "1111" + game.player_names[game.Get_Player().name] + variableStats + std::to_string((int)game.Get_Player().def.gender) + std::to_string((int)game.Get_Player().def.species) + std::to_string((int)game.Get_Player().def.unitClass) + std::to_string((int)game.Get_Player().def.alignment);
    std::cout << "3" + stats << " Char stats sent!" << std::endl;
    return "3" + stats;
  }

  void Spawn(Game::Instance &game, int level, Component::Position location, int x, int y, const std::basic_string<char> &characterCreate) {
//    game.objects[level][location].unitsString += "2";
    // loop through the map x times and lok for 2x2 squares
    // set entities to be in the center of the square
    // I need to send the char and the offset in the map g0317
    auto length = characterCreate.size();

    std::cout << "Character create: " << characterCreate << std::endl;
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

    Spawn::Add_Unit(game.objects[level][location], level, location, x, y, game.player_id, gender, species, unitClass, alignment);

    game.player_names.push_back(name);
    game.player_id++;
    std::cout << "size: " << game.objects[level][location].units.size() << std::endl;
    game.objects[level][location].units.at(0).health = 999;
    game.objects[level][location].units.at(0).healthMax = 999;
    std::cout << "health: " << game.objects[level][location].units.at(0).health << std::endl;
    std::string xStr = Utils::Prepend_Zero(x);
    std::string yStr = Utils::Prepend_Zero(y);

//    game.objects[level][location].unitsString += (std::to_string(Spawn::Get_Unit_Char(species)) + xStr + yStr);
  }

}