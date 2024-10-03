#include "unordered_map"
#include "iostream"

#include "game.h"
#include "update.h"
#include "units.h"
#include "map.h"
#include "collision.h"
#include "attack.h"
#include "movement.h"
#include "utils.h"
#include "pathing.h"
#include "spawn.h"

namespace Update {
  struct Move {
    int x = 0;
    int y = 0;
  };

  std::unordered_map<char, Move> updatePosition = {
    {'w', {0,-1}},
    {'a', {-1,0}},
    {'s', {0,1}},
    {'d', {1,0}},
    {'r', {0,0}}
  };

  void Update_Player_Position(Game::State &game, int &px, int &py, int &x, int &y, Units::Species &species) {
    auto &player = game.Get_Player();
    std::cout << "initial player position: " << player.position.x << " " << player.position.y << std::endl;
    std::cout << "initial player location: " << player.location.x << " " << player.location.y << std::endl;

    bool newChunk = false;

    //if at edge of map
    if (player.position.x + x < 0 || player.position.x + x >= Component::mapWidth || player.position.y + y < 0 || player.position.y + y >= Component::mapWidth) {
      auto formerPos = player.position;
      auto location = player.location;

      if (player.position.x + x < 0) {
        player.location.x--;
        player.position.x = Component::mapWidth - 1;
        newChunk = true;
      } else if (player.position.x + x >= Component::mapWidth) {
        player.location.x++;
        player.position.x = 0;
        newChunk = true;
      } else if (player.position.y + y < 0) {
        player.location.y--;
        player.position.y = Component::mapWidth - 1;
        newChunk = true;
      } else if (player.position.y + y >= Component::mapWidth) {
        player.location.y++;
        player.position.y = 0;
        newChunk = true;
      }
      if (newChunk) {
        std::cout << "Moving to new chunk..." << std::endl;
        Map::Update(game, formerPos, player.position, location, player.location, Spawn::Get_Unit_Char(player.def.species));
        Units::Update_Unit_Position(game.objects.unitPositions, formerPos.x, formerPos.y, player.position.x, player.position.y);
      }
    }

    if (!newChunk) {
      Map::Update(game, px, py, x, y, Spawn::Get_Unit_Char(species));
      Units::Update_Unit_Position(game.objects.unitPositions, px, py, px + x, py + y);
      Movement::Move(game, x, y);
    }

    Units::Update_UnitsString(game.objects.unitsString, x, y);
    std::cout << "new player position: " << player.position.x << " " << player.position.y << std::endl;
    std::cout << "new player location: " << player.location.x << " " << player.location.y << std::endl;
  }

  bool Check_For_Target(const Component::Position &position, const Component::Position &target) {
    if (abs(position.x - target.x) < 6 && abs(position.y - target.y) < 6)
      return true;
    return false;
  }

  void Update_Enemies(Game::State &game) {
    auto &units = game.objects.units;
    auto &player = game.Get_Player();

    for (int i = 1; i < units.size(); i++) {
      if (units[i].health <= 0) {
        std::cout << "unit dead" << std::endl;
        continue;
      }
      //if player is in vision
      if (Check_For_Target(units[i].position, player.position)) {
        std::cout << "player in vision, moving towards!" << std::endl;
        // cache position
        Component::Position former = units[i].position;
        // calculate next cell
        Component::Position moveTo = Pathing::Move_To(game.map[units[i].level][units[i].location].pathing, units[i].position, player.position);
        std::cout << "unit moves from: " << former.x << ", " << former.y << std::endl;
        std::cout << "unit moves to: " << moveTo.x << ", " << moveTo.y << std::endl;
        // check next cell and move/attack
        if (Map::Get_Adjacent_Tile(game, former.x + moveTo.x, former.y + moveTo.y).at(0) == Spawn::Get_Unit_Char(player.def.species)) {
          std::cout << "unit attacks player" << std::endl;
          Attack::Melee(game.objects, game.map[units[i].level][units[i].location].defaultChunk, game.map[units[i].level][units[i].location].chunk, former.x, former.y, moveTo.x, moveTo.y);
          continue;
        }

        units[i].position.x += moveTo.x;
        units[i].position.y += moveTo.y;

        Map::Update(game, former.x, former.y, moveTo.x, moveTo.y, Spawn::Get_Unit_Char(units[i].def.species));
        auto map = Map::Get_Map(game.map[units[i].level][units[i].location].chunk);
        Pathing::Update(game.map[units[i].level][units[i].location].pathing, map);
        Units::Update_Unit_Position(game.objects.unitPositions, former.x, former.y, units[i].position.x, units[i].position.y);
      }
      else {
        std::cout << "player not in vision" << std::endl;
      }
    }

    auto mapString = Map::Get_Map(game.map[game.level][game.location].chunk);
    std::cout << "Drawing map: "<< std::endl;
    for (int i = 0; i < 99; i++) {
      std::cout << mapString.substr(i * 99, 99) << std::endl;
    }
  }

  std::string Update_Player(Game::State &game, const char *direction) {
    Move move;
    move = updatePosition[*direction];

    std::cout << "num entities on update: " << game.objects.units.size() << std::endl;
    Units::Unit &player = game.Get_Player();
    std::cout << "successfully grabbed player from units[]" << std::endl;

    //rest
    if (move.x == 0 && move.y == 0) {
      std::string r = "r";
      std::cout << "rest" << std::endl;
      return r + " " + "  " + "1";
    }

    // collision
    if (Collision::Wall_Collision(game, player.position.x, player.position.y, move.x, move.y)) {
      std::cout << "wall collision" << std::endl;
      std::string c = "c";
      return c + " " + "  " + "1";
    }
    // if the nearby cell is an enemy, attack
    auto melee = Attack::Melee(game.objects, game.map[game.level][game.location].defaultChunk, game.map[game.level][game.location].chunk, player.position.x, player.position.y, move.x, move.y);
    if (melee.damageDone > 0 && !melee.isDead) {
      std::cout << "attack goblin" << std::endl;
      return "m" + melee.target + Utils::Prepend_Zero(melee.damageDone) + "1";
    }

    // if the unit survives, return, else move to the cell
    Update_Player_Position(game, player.position.x, player.position.y, move.x, move.y, player.def.species);
    Map::Check_Map_Chunk(game);

    std::string m = direction;
    if (melee.isDead) {
      std::cout << "goblin dead" << std::endl;
      return m + melee.target + Utils::Prepend_Zero(melee.damageDone) + "0";
    }
    return m + " " + "  " + "1";
  }

  std::string Update_Units(Game::State &game, const char *direction) {
    auto action = Update_Player(game, direction);
    Update_Enemies(game);
    return action;
  }

}
