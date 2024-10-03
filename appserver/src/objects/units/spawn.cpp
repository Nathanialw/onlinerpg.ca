//
// Created by desktop on 9/25/24.
//
#include "spawn.h"
#include "map.h"
#include "units.h"
#include "utils.h"
#include "procgen.h"
#include "chunk.h"

namespace Spawn {

  char unitChars[(int)Units::Species::SIZE] = {'a',   'b',    'c',
                                               'd',   'e',    'f',    'g',
                                               'h',   'i',    'j',    'k',
                                               'l',   'm',    'n',    'o',
                                               'p',   'q',    'r',    's',
                                               't',   'u',    'v',    'w',
                                               'x',   'y',    'z',    'A',
                                               'B',   'C',    'D',    'E',   'F',
                                               'G',   'H',    'I',    'J',   'K',
                                               'L',   'M',    'N',    'O',   'P',
                                               'Q',   'R',    'S',    'T',   'U',
                                               'V',   'W',    'X',    'Y',   'Z', ' '};

  char Get_Unit_Char(Units::Species species) {
    return unitChars[(int)species];
  }

  void Add_Unit(Units::Objects &objects, int level, Component::Position location, int x, int y, const std::string &name, Units::Gender gender, Units::Species species, Units::Class unitClass, Units::Alignment alignment) {
    Units::Unit unit{};
    unit.name = name;
    unit.def.gender = gender;
    unit.def.species = species;
    unit.def.unitClass = unitClass;
    unit.def.alignment = alignment;
    unit.position.x = x;
    unit.position.y = y;

    unit.level = level;
    unit.location = location;

    auto &units = objects.units;
    auto &unitsPositions = objects.unitPositions;

    auto &emptyUnitSlots = objects.emptyUnitSlots;
    if (emptyUnitSlots.empty()) {
      units.emplace_back(unit);
    } else {
      units.at(emptyUnitSlots.back()) = unit;
      emptyUnitSlots.pop_back();
    }

    Component::Position pos = {x, y};
    unitsPositions.emplace(pos, units.size() - 1);
  }

  std::vector<Placement> Spawn_Unit(std::vector<Chunk::Room> &rooms) {
    std::vector<Placement> placements;
    Placement placement{};
    Proc_Gen::Seed seed;

    for (const auto &room : rooms) {
      seed.seed = Proc_Gen::Create_Initial_Seed(room.x, room.y);
      placement.x = Proc_Gen::Random_Int(room.x, room.x + room.w, seed);
      placement.y = Proc_Gen::Random_Int(room.y, room.y + room.h, seed);
      placements.emplace_back(placement);
    }
    return placements;
  }

  bool Add_Object(Units::Objects &objects, int level, Component::Position location, std::string &group, int x, int y) {
    if (x > Component::mapWidth - 1 || y > Component::mapWidth - 1 || x < 1 || y < 1) {
      group.clear();
      return false;
    } else {
      group += Utils::Prepend_Zero(x);
      group += Utils::Prepend_Zero(y);
      Add_Unit(objects, level, location, x, y, "Blargh", Units::Gender::MALE, Units::Species::GOBLIN, Units::Class::FIGHTER, Units::Alignment::EVIL);
      return true;
    }
  }

  std::string Random_Entities(Units::Objects &objects, int level, Component::Position location, const char entityType, int numEntities, int x, int y) {
    std::string group;
    int tries = 10;
  reRoll:
    if (tries == 0) {
      return group;
    }
    for (int i = 0; i < numEntities; ++i) {
      group += entityType;
      if (!Add_Object(objects, level, location, group, x + i, y + i)) {
        tries--;
        goto reRoll;
      }
    }
    return group;
  }

  void Place_Entities_On_Map(std::vector<Chunk::Room> &rooms, int level, Component::Position location, Units::Objects &objects) {
    auto placements = Spawn_Unit(rooms);
    std::cout << "num placements: " << placements.size() << std::endl;

    for (const auto &placement : placements) {
      int numMonsters = rand() % 4;
      auto unitData = Random_Entities(objects, level, location, unitChars[(int)Units::Species::GOBLIN], numMonsters, placement.x, placement.y);
      objects.unitsString += unitData;
      std::cout << "units added: " << unitData << std::endl;
    }

    std::cout << "init num entities: " << objects.units.size() << std::endl;
  }

  //we beed the chunk that the unit is being spawned in
  void Init(int level, Component::Position location, char chunk[Component::mapWidth][Component::mapWidth], std::vector<Chunk::Room> &rooms, Units::Objects &objects) {

    if (objects.units.empty()) { //To save the 0 index for the player
      Units::Unit playerPlaceholder;
      objects.units.emplace_back(playerPlaceholder);
    }
    Place_Entities_On_Map(rooms, level, location, objects);

    for (auto &unit : objects.units) {
        Map::Set_Tile(chunk, unit.position.x, unit.position.y, unitChars[(int)unit.def.species]);
    }
    std::cout << "units inited" << std::endl;

  }
}