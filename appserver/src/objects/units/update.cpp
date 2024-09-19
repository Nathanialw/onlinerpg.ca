
#include "update.h"
#include "units.h"
#include "map.h"
#include "collision.h"
#include "attack.h"
#include "movement.h"
#include "iostream"
#include "unordered_map"
#include "utils.h"

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

  std::string Update_Player(const char *direction) {
    Move move;
    move = updatePosition[*direction];

    std::cout << "num entities on update: " << Units::Get_Units()->size() << std::endl;
    auto &player = Units::Get_Units()->at(0);
    std::cout << "successfully grabbed player from units[]" << std::endl;

    // collision
    if (Collision::Wall_Collision(player.x, player.y, move.x, move.y)) {
      std::cout << "wall collision" << std::endl;
      std::string c = "c";
      return c + " " + "  " + "1";
    }
    // if the nearby cell is an enemy, attack
    auto melee = Attack::Melee(player.x, player.y, move.x, move.y);
    if (melee.damageDone > 0 && !melee.isDead) {
      std::cout << "attack goblin" << std::endl;
      return "m" + melee.target + Utils::Prepend_Zero(melee.damageDone) + "1";
    }

    // if the unit survives, return, else move to the cell
    Map::Update(player.x, player.y, move.x, move.y, Units::Get_Unit_Char(player.def.species));
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
  }

}
