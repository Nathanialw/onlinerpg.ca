//
// Created by desktop on 9/25/24.
//
#include "spawn.h"
#include "map.h"
#include "units.h"
#include "utils.h"

namespace Spawn {
  const int mapWidth = Map::Get_Map_Wdth();
  std::vector<int> emptyUnitSlots;

  std::string unitChars[(int)Units::Species::SIZE] = {"a",    "b",    "c",
                                               "d",   "e",    "f",    "g",
                                               "h",   "i",    "j",    "k",
                                               "l",   "m",    "n",    "o",
                                               "p",   "q",    "r",    "s",
                                               "t",   "u",    "v",    "w",
                                               "x",   "y",    "z",    "A",
                                               "B",  "C",   "D",   "E",   "F",
                                               "G",   "H",   "I",   "J",   "K",
                                               "L",   "M",   "N",   "O",   "P",
                                               "Q",   "R",   "S",   "T",   "U",
                                               "V",   "W",   "X",   "Y",   "Z", " "};

  std::string Get_Unit_Char(Units::Species species) {
    return unitChars[(int)species];
  }

  Placement Random_Placement() {
    Placement placement{};
    placement.x = rand() % mapWidth;
    placement.y = rand() % mapWidth;
    return placement;
  }

  void Add_Unit(int x, int y, const std::string &name, Units::Gender gender, Units::Species species, Units::Class unitClass, Units::Alignment alignment) {
    Units::Unit unit{};
    unit.name = name;
    unit.def.gender = gender;
    unit.def.species = species;
    unit.def.unitClass = unitClass;
    unit.def.alignment = alignment;
    unit.position.x = x;
    unit.position.y = y;

    auto units = Units::Get_Units();
    auto unitsPositions = Units::Get_Unit_Positions();

    if (emptyUnitSlots.empty()) {
      units->push_back(unit);
    } else {
      units->at(emptyUnitSlots.back()) = unit;
      emptyUnitSlots.pop_back();
    }

    Units::UnitPosition pos = {x, y};

    unitsPositions->emplace(pos, units->size() - 1);
  }

  bool Add_Object(std::string &group, int x, int y) {
    if (x > mapWidth - 1 || y > mapWidth - 1 || x < 1 || y < 1) {
      group.clear();
      return false;
    } else {
      group += Utils::Prepend_Zero(x);
      group += Utils::Prepend_Zero(y);
      Add_Unit(x, y, "Blargh", Units::Gender::MALE, Units::Species::GOBLIN, Units::Class::FIGHTER, Units::Alignment::EVIL);
      return true;
    }
  }

  std::string Random_Entities(const char* entityType, int numEntities) {
    std::string group;
  reRoll:
    Placement placement = Random_Placement();
    for (int i = 0; i < numEntities; ++i) {
      group += entityType;
      if (!Add_Object(group, placement.x + i, placement.y + i))
        goto reRoll;
    }
    return group;
  }


  std::string Place_Entities_On_Map(std::basic_string<char> characterCreate) {
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

    Add_Unit(6, 6, name, gender, species, unitClass, alignment);
    auto units = *Units::Get_Units();
    units[0].health = 100;
    units[0].healthMax = 100;

    mapEntities += unitChars[(int)unitClass] + "0606";

    for (int i = 0; i < 5; ++i) {
      int numMonsters = rand() % 4;
      mapEntities += Random_Entities(unitChars[(int)Units::Species::GOBLIN].c_str(), numMonsters);
    }
    std::cout << "init num entities: " << units.size() << std::endl;
    return mapEntities;
  }

  void Spawn_Unit(int x, int y, int species) {
    //for each big room
    auto largeRooms = Map::Get_Large_Rooms();
    for (const auto &room : largeRooms) {
        //if the unit is in the room
        if (x >= room.x && x < room.x + room.w && y >= room.y && y < room.y + room.h) {
          //add the unit to the units vector
//          Add_Unit(x, y, species);
          //set the tile to the unit
          Map::Set_Tile(x, y, "u");
          return;
        }
    }
  }

  void Init(const std::basic_string<char> &characterCreate) {
    Units::Set_Units_String(Place_Entities_On_Map(characterCreate));

    for (auto &unit : *Units::Get_Units()) {
        Map::Set_Tile(unit.position.x, unit.position.y, unitChars[(int)unit.def.species]);
    }
  }
}