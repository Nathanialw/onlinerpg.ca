#include "unordered_map"
#include "iostream"

#include "update.h"
#include "units.h"
#include "map.h"
#include "collision.h"
#include "attack.h"
#include "movement.h"
#include "utils.h"
#include "pathing.h"

namespace Update {
  struct Move {
    int x = 0;
    int y = 0;
  };

  std::unordered_map<char, Move> updatePosition = {
    {'w', {0,-1}},
    {'a', {-1,0}},
    {'s', {0,1}},
    {'d', {1,0}}
  };

  void Update_Enemies() {
    auto &player = Units::Get_Units()->at(0);
    auto &units = *Units::Get_Units();

    for (int i = 1; i < units.size(); i++) {

      //if player is in vision
      //cache position
      Component::Position former = units[i].position;
      //calculate next cell
      Component::Position moveTo = Pathing::Move_To(units[i].position, player.position);
      //check next cell and move/attack
      if (Map::Get_Adjacent_Tile(former.x + moveTo.x, former.y + moveTo.y) == "h") {
        std::cout << "goblin attacks player" << std::endl;
        continue;
      }
      units[i].position.x += moveTo.x;
      units[i].position.y += moveTo.y;
      Map::Update(former.x, former.y, moveTo.x, moveTo.y, Units::Get_Unit_Char(units[i].def.species));
      Pathing::Update(Map::Get_Map());
      Units::Update_Unit_Position(former.x, former.y, units[i].position.x, units[i].position.y);
    }

    auto mapString = Map::Get_Map();
    std::cout << "Drawing map: "<< std::endl;
    for (int i = 0; i < 100; i++) {
      std::cout << mapString.substr(i * 100, 100) << std::endl;
    }
  }

  std::string Update_Player(const char *direction) {
    Move move;
    move = updatePosition[*direction];

    std::cout << "num entities on update: " << Units::Get_Units()->size() << std::endl;
    auto &player = Units::Get_Units()->at(0);
    std::cout << "successfully grabbed player from units[]" << std::endl;

    // collision
    if (Collision::Wall_Collision(player.position.x, player.position.y, move.x, move.y)) {
      std::cout << "wall collision" << std::endl;
      std::string c = "c";
      return c + " " + "  " + "1";
    }
    // if the nearby cell is an enemy, attack
    auto melee = Attack::Melee(player.position.x, player.position.y, move.x, move.y);
    if (melee.damageDone > 0 && !melee.isDead) {
      std::cout << "attack goblin" << std::endl;
      return "m" + melee.target + Utils::Prepend_Zero(melee.damageDone) + "1";
    }

    // if the unit survives, return, else move to the cell
    Map::Update(player.position.x, player.position.y, move.x, move.y, Units::Get_Unit_Char(player.def.species));
    Movement::Move(move.x, move.y);
    Units::Update_UnitsString(move.x, move.y);

    std::string m = direction;
    if (melee.isDead) {
      std::cout << "goblin dead" << std::endl;
      return m + melee.target + Utils::Prepend_Zero(melee.damageDone) + "0";
    }
    return m + " " + "  " + "1";
  }

  void Update_Units(const char *direction) {
    Update_Player(direction);
    Update_Enemies();
  }

}
