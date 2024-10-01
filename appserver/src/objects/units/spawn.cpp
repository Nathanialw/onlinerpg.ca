//
// Created by desktop on 9/25/24.
//
#include "spawn.h"
#include "map.h"
#include "units.h"
#include "utils.h"
#include "procgen.h"

namespace Spawn {

  std::string unitChars[(int)Units::Species::SIZE] = {"a",    "b",    "c",
                                               "d",   "e",    "f",    "g",
                                               "h",   "i",    "j",    "k",
                                               "l",   "m",    "n",    "o",
                                               "p",   "q",    "r",    "s",
                                               "t",   "u",    "v",    "w",
                                               "x",   "y",    "z",    "A",
                                               "B",   "C",    "D",    "E",   "F",
                                               "G",   "H",    "I",    "J",   "K",
                                               "L",   "M",    "N",    "O",   "P",
                                               "Q",   "R",    "S",    "T",   "U",
                                               "V",   "W",    "X",    "Y",   "Z", " "};

  std::string Get_Unit_Char(Units::Species species) {
    return unitChars[(int)species];
  }

  void Add_Unit(Game::State &game, int x, int y, const std::string &name, Units::Gender gender, Units::Species species, Units::Class unitClass, Units::Alignment alignment) {
    Units::Unit unit{};
    unit.name = name;
    unit.def.gender = gender;
    unit.def.species = species;
    unit.def.unitClass = unitClass;
    unit.def.alignment = alignment;
    unit.position.x = x;
    unit.position.y = y;

    auto &units = game.units;
    auto &unitsPositions = game.unitPositions;

    auto &emptyUnitSlots = game.emptyUnitSlots;
    if (emptyUnitSlots.empty()) {
      units.emplace_back(unit);
    } else {
      units.at(emptyUnitSlots.back()) = unit;
      emptyUnitSlots.pop_back();
    }

    Component::Position pos = {x, y};
    unitsPositions.emplace(pos, units.size() - 1);
  }

  std::vector<Placement> Spawn_Unit() {
    std::vector<Placement> placements;
    Placement placement{};
    Proc_Gen::Seed seed;

    for (const auto &room : Map::Get_Large_Rooms()) {
      seed.seed = Proc_Gen::Create_Initial_Seed(room.x, room.y);
      placement.x = Proc_Gen::Random_Int(room.x, room.x + room.w, seed);
      placement.y = Proc_Gen::Random_Int(room.y, room.y + room.h, seed);
      placements.emplace_back(placement);
    }
    return placements;
  }

  bool Add_Object(Game::State &game, std::string &group, int x, int y) {
    if (x > Component::mapWidth - 1 || y > Component::mapWidth - 1 || x < 1 || y < 1) {
      group.clear();
      return false;
    } else {
      group += Utils::Prepend_Zero(x);
      group += Utils::Prepend_Zero(y);
      Add_Unit(game, x, y, "Blargh", Units::Gender::MALE, Units::Species::GOBLIN, Units::Class::FIGHTER, Units::Alignment::EVIL);
      return true;
    }
  }

  std::string Random_Entities(Game::State &game, const char* entityType, int numEntities, int x, int y) {
    std::string group;
    int tries = 10;
  reRoll:
    if (tries == 0) {
      return group;
    }
    for (int i = 0; i < numEntities; ++i) {
      group += entityType;
      if (!Add_Object(game, group, x + i, y + i)) {
        tries--;
        goto reRoll;
      }
    }
    return group;
  }

  std::string Place_Entities_On_Map(Game::State &game, const std::basic_string<char> &characterCreate) {
    std::string mapEntities = "2";
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

    Add_Unit(game, 6, 6, name, gender, species, unitClass, alignment);
    auto &units = game.units;
    std::cout << "size: " << units.size() << std::endl;
    units.at(0).health = 100;
    units.at(0).healthMax = 100;
    std::cout << "health: " << units.at(0).health << std::endl;

    mapEntities += unitChars[(int)unitClass] + "0606";

    auto placements = Spawn_Unit();
    std::cout << "num placements: " << placements.size() << std::endl;

    for (const auto &placement : placements) {
      int numMonsters = rand() % 4;
      auto asd = Random_Entities(game, unitChars[(int)Units::Species::GOBLIN].c_str(), numMonsters, placement.x, placement.y);
      mapEntities += asd;
      std::cout << "units added: " << asd << std::endl;
    }

    std::cout << "init num entities: " << units.size() << std::endl;
    return mapEntities;
  }

  void Init(Game::State &game, const std::basic_string<char> &characterCreate) {
    game.unitsString = Place_Entities_On_Map(game, characterCreate);

    for (auto &unit : game.units) {
        Map::Set_Tile(game, unit.position.x, unit.position.y, unitChars[(int)unit.def.species]);
    }
  }
}