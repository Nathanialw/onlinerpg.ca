//
// Created by desktop on 9/19/24.
//
#include "string"
#include "goblin.h"
#include "units.h"
#include "utils.h"
#include "iostream"
#include "game.h"

// name
// gender
// pic
// health/maxhealth
// damage range
// AC
// speed
// vision
// alignment

//type? (fire/ice/etc maybe not sure if will use)

namespace Species {
  std::string Get_Unit_Data_As_string(Game::Instance &game, const std::string &msg) {
    int mapPositionX = game.Get_Player().position.x - game.Get_Player().vision + std::stoi(msg.substr(0, 2));
    int mapPositionY = game.Get_Player().position.y - game.Get_Player().vision + std::stoi(msg.substr(2, 2));

    //will need to use mouse coords to determine level/location, but for now you can only get from the same map chunk/level as the player
    auto unit = Units::Get_Unit_At_Position(game.objects[game.Get_Player().level][game.Get_Player().location].units, game.objects[game.Get_Player().level][game.Get_Player().location].unitPositions, mapPositionX, mapPositionY);

    //unit ID for the DB
    std::cout << "unitID  int8: " << unit.unitID << std::endl;
    auto unitID = Utils::Prepend_Zero_By_Digits(unit.unitID, 3);
    std::cout << "unitID str: " << unitID << std::endl;
        //name uID from "names" table, save in unit class
      //vision from DB
      //speed from DB
      //alignment from DB
      //bio from DB
      //pic from DB

    //append to the message
      //age random generate
      //health random generate + level + items
      //gender random generate
      //damage random generate + items
      //AC random generate + items

    std::cout << "unit name int16: " << unit.name << std::endl;
    auto name = Utils::Prepend_Zero_By_Digits(unit.name, 3);
    std::cout << "unit name str: " << name << std::endl;

    auto age = Utils::Prepend_Zero_By_Digits(unit.age, 3);
    std::string gender = std::to_string((int)unit.def.gender);
//    std::string alignment = std::to_string((int)unit.def.alignment);
    //assets/species/goblin.png   this would be a good opportunity to try using a CDN
//    auto pic = "5";
    auto health = Utils::Prepend_Zero_3Digit(unit.health) + Utils::Prepend_Zero_3Digit(unit.healthMax);
    auto damage = Utils::Prepend_Zero(unit.minDamage) + Utils::Prepend_Zero(unit.maxDamage);
    auto AC = Utils::Prepend_Zero(unit.AC);
//    auto speed = std::to_string(unit.speed);
//    auto vision = Utils::Prepend_Zero(unit.vision);
//    std::string bio = "Swamp goblins inhabit the murky, mist-shrouded wetlands of the Shadowlands, where they thrive in the damp, oxygen-poor environment. These peculiar creatures have adapted to their surroundings, developing scaly, moss-covered skin that blends seamlessly with the surrounding vegetation. Their eyes glow like lanterns in the dark, emitting a faint, eerie light that allows them to navigate the treacherous, waterlogged terrain with ease. Their limbs are long and spindly, ending in webbed fingers and toes that enable them to propel themselves through the murky waters with surprising agility.";
//    return name + "_" + age + gender + alignment + pic + "_" + health + damage + AC + speed + vision + bio;
    return unitID + name + age + gender + health + damage + AC;
  }
}