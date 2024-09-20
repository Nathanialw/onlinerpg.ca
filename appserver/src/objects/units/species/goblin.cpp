//
// Created by desktop on 9/19/24.
//
#include "string"
#include "goblin.h"
#include "units.h"
#include "utils.h"
#include "iostream"

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
  std::string Get_Unit_Data_As_string(const std::string &msg) {
    auto player = Units::Get_Player();
    int mapPositionx = player.x - player.vision + std::stoi(msg.substr(0, 2));
    int mapPositiony = player.y - player.vision + std::stoi(msg.substr(2, 2));

    auto unit = Units::Get_Unit_At_Position(mapPositionx, mapPositiony);

    auto name = unit.name;
    std::string gender = std::to_string((int)unit.def.gender);
    std::string alignment = std::to_string((int)unit.def.alignment);
    //assets/species/goblin.png   this would be a good opportunity to try using a CDN
    auto pic = "5";
    auto health = std::to_string(unit.health) + std::to_string(unit.healthMax);
    auto damage = Utils::Prepend_Zero(unit.minDamage) + Utils::Prepend_Zero(unit.maxDamage);
    auto AC = Utils::Prepend_Zero(unit.AC);
    auto speed = std::to_string(unit.speed);
    auto vision = Utils::Prepend_Zero(unit.vision);
    std::string bio = "Swamp goblins inhabit the murky, mist-shrouded wetlands of the Shadowlands, where they thrive in the damp, oxygen-poor environment. These peculiar creatures have adapted to their surroundings, developing scaly, moss-covered skin that blends seamlessly with the surrounding vegetation. Their eyes glow like lanterns in the dark, emitting a faint, eerie light that allows them to navigate the treacherous, waterlogged terrain with ease. Their limbs are long and spindly, ending in webbed fingers and toes that enable them to propel themselves through the murky waters with surprising agility. \nDespite their unsettling appearance, swamp goblins are a tribal people, living in small, close-knit communities centered around family ties. They possess a unique ability to communicate with the swamp’s native creatures, including the massive, lumbering swamp donkeys that roam the wetlands. This affinity for the natural world has led to a peculiar form of symbiosis, where the goblins prey on the donkeys’ young, but also provide a vital service by controlling the population and maintaining the delicate balance of the ecosystem. Theirs is a harsh, unforgiving existence, but one that is deeply intertwined with the swamp itself, and they have evolved to thrive in this strange, twilight world.";

    return name + "_" + gender + alignment + pic + "_" + health + damage + AC + speed + vision + bio;
  }
}