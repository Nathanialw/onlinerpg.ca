#include "update.h"
#include "units.h"
#include "map.h"
#include "collision.h"
#include "attack.h"
#include "movement.h"
#include "iostream"
#include "unordered_map"
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


    auto units = *Units::Get_Units();
    for (int i = 1; i < units.size(); i++) {

      //if player is in vision
      std::string map;
      Component::Position former = units[i].position;
      Pathing::Move_To(units[i].position, player.position, map);
      Map::Update(former.x, former.y, units[i].position.x, units[i].position.y, Units::Get_Unit_Char(units[i].def.species));

//      Units::Update_UnitsString(unit.x, unit.y);

      //if they move onto the player, record as attack to send to client
    }

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
