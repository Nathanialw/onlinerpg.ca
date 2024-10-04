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

    std::cout << "initial player position: " << game.Get_Player().position.x << " " << game.Get_Player().position.y << std::endl;
    std::cout << "initial player location: " << game.Get_Player().location.x << " " << game.Get_Player().location.y << std::endl;

    bool newChunk = false;

    //if at edge of map
    if (game.Get_Player().position.x + x < 0 || game.Get_Player().position.x + x >= Component::mapWidth || game.Get_Player().position.y + y < 0 || game.Get_Player().position.y + y >= Component::mapWidth) {
      auto formerPos = game.Get_Player().position;
      auto location = game.Get_Player().location;
      auto level = game.Get_Player().level;
      std::cout << "new position: " << px + x << ", " << py + y << std::endl;

      if (game.Get_Player().position.x + x < 0) {
        std::cout << "player position x less than 0 moving to left chunk" << std::endl;
        game.Get_Player().location.x--;
        game.Get_Player().position.x = Component::mapWidth - 1;
        game.location.x--;
        newChunk = true;
      } else if (game.Get_Player().position.x + x >= Component::mapWidth) {
        std::cout << "player position x greater than map width moving to right chunk" << std::endl;
        game.Get_Player().location.x++;
        game.Get_Player().position.x = 0;
        game.location.x++;
        newChunk = true;
      } else if (game.Get_Player().position.y + y < 0) {
        std::cout << "player position y less than 0 moving to top chunk" << std::endl;
        game.Get_Player().location.y--;
        game.Get_Player().position.y = Component::mapWidth - 1;
        game.location.y--;
        newChunk = true;
      } else if (game.Get_Player().position.y + y >= Component::mapWidth) {
        std::cout << "player position y greater than map width moving to bottom chunk" << std::endl;
        game.Get_Player().location.y++;
        game.Get_Player().position.y = 0;
        game.location.y++;
        newChunk = true;
      }
      if (newChunk) {
        std::cout << "old player location: " << game.objects[level][location].units[0].location.x << ", " << game.objects[level][location].units[0].location.y << std::endl;
        std::cout << "old player player position: " << game.objects[level][location].units[0].position.x << ", " << game.objects[level][location].units[0].position.y << std::endl;
        game.objects[game.Get_Player().level][game.Get_Player().location].units[0] = game.objects[level][location].units[0];
        std::cout << "position: " << game.objects[game.level][game.location].units[0].position.x << ", " << game.objects[game.level][game.location].units[0].position.y << std::endl;
        std::cout << "location: " << game.objects[game.level][game.location].units[0].location.x << ", " << game.objects[game.level][game.location].units[0].location.y << std::endl;


        Units::Remove_Unit(game.objects[level][location].unitPositions, game.objects[level][location].emptyUnitSlots, formerPos.x, formerPos.y);
        game.objects[game.Get_Player().level][game.Get_Player().location].unitPositions.emplace(game.Get_Player().position, 0);
        //update map
        Map::Update(game, game.Get_Player().level, formerPos, game.Get_Player().position, location, game.Get_Player().location, Spawn::Get_Unit_Char(game.Get_Player().def.species));
      }
    }

    if (!newChunk) {
      Map::Update(game, game.Get_Player().level, game.Get_Player().location, px, py, x, y, Spawn::Get_Unit_Char(species));
      Units::Update_Unit_Position(game.objects[game.Get_Player().level][game.Get_Player().location].unitPositions, px, py, px + x, py + y);
      Movement::Move(game, x, y);
    }

//    Units::Update_UnitsString(game.objects[player.level][player.location].unitsString, x, y);
    std::cout << "new player position: " << game.Get_Player().position.x << " " << game.Get_Player().position.y << std::endl;
    std::cout << "new player location: " << game.Get_Player().location.x << " " << game.Get_Player().location.y << std::endl;
    std::cout << "-------------------" << std::endl;
  }

  bool Check_For_Target(const Component::Position &position, const Component::Position &target) {
    if (abs(position.x - target.x) < 6 && abs(position.y - target.y) < 6)
      return true;
    return false;
  }

  void Update_Enemies(Game::State &game) {
    // cycle through all units

    for (auto &level : game.objects) {
      auto &chunks = level;
      for (auto &chunk : chunks) {
        for (int i = 1; i < chunk.second.units.size(); ++i) {
          auto &unit = chunk.second.units[i];
          if (unit.health <= 0) {
            std::cout << "unit dead" << std::endl;
             continue;
          }

          //if player in same map chunk
          if (game.Get_Player().location == unit.location) {
            //if player is in vision
            if (Check_For_Target(unit.position, game.Get_Player().position)) {
              std::cout << "player in vision, moving towards!" << std::endl;
              // cache position
              Component::Position former = unit.position;
              // calculate next cell
              Component::Position moveTo = Pathing::Move_To(game.map[unit.level][unit.location].pathing, unit.position, game.Get_Player().position);
              std::cout << "unit moves from: " << former.x << ", " << former.y << std::endl;
              std::cout << "unit moves to: " << moveTo.x << ", " << moveTo.y << std::endl;
              // check next cell and move/attack
              if (Map::Get_Adjacent_Tile(game, unit.level, unit.location, former.x + moveTo.x, former.y + moveTo.y).at(0) == Spawn::Get_Unit_Char(game.Get_Player().def.species)) {
                std::cout << "unit attacks player" << std::endl;
                Attack::Melee(game.objects[unit.level][unit.location], game.map[unit.level][unit.location].defaultChunk, game.map[unit.level][unit.location].chunk, former.x, former.y, moveTo.x, moveTo.y);
                continue;
              }

              unit.position.x += moveTo.x;
              unit.position.y += moveTo.y;

              Map::Update(game, unit.level, unit.location, former.x, former.y, moveTo.x, moveTo.y, Spawn::Get_Unit_Char(unit.def.species));
              auto map = Map::Get_Map(game.map[unit.level][unit.location].chunk);
              Pathing::Update(game.map[unit.level][unit.location].pathing, map);
              Units::Update_Unit_Position(game.objects[unit.level][unit.location].unitPositions, former.x, former.y, unit.position.x, unit.position.y);
            }
            else {
              std::cout << "player not in vision" << std::endl;
            }
          }
        }
      }
    }

    auto mapString = Map::Get_Map(game.map[game.Get_Player().level][game.Get_Player().location].chunk);
    std::cout << "Drawing map: "<< std::endl;
    for (int i = 0; i < 99; i++) {
      std::cout << mapString.substr(i * 99, 99) << std::endl;
    }
  }

  std::string Update_Player(Game::State &game, const char *direction) {
    Move move;
    move = updatePosition[*direction];

    std::cout << "num entities on update: " << game.objects[game.Get_Player().level][game.Get_Player().location].units.size() << std::endl;
    std::cout << "successfully grabbed player from units[]" << std::endl;

    //rest
    if (move.x == 0 && move.y == 0) {
      std::string r = "r";
      std::cout << "rest" << std::endl;
      return r + " " + "  " + "1";
    }

    // collision
    if (Collision::Wall_Collision(game, game.Get_Player().level, game.Get_Player().location, game.Get_Player().position.x, game.Get_Player().position.y, move.x, move.y)) {
      std::cout << "wall collision" << std::endl;
      std::string c = "c";
      return c + " " + "  " + "1";
    }
    // if the nearby cell is an enemy, attack
    auto melee = Attack::Melee(game.objects[game.Get_Player().level][game.Get_Player().location], game.map[game.Get_Player().level][game.Get_Player().location].defaultChunk, game.map[game.Get_Player().level][game.Get_Player().location].chunk, game.Get_Player().position.x, game.Get_Player().position.y, move.x, move.y);
    if (melee.damageDone > 0 && !melee.isDead) {
      std::cout << "attack goblin" << std::endl;
      return "m" + melee.target + Utils::Prepend_Zero(melee.damageDone) + "1";
    }

    // if the unit survives, return, else move to the cell
    Update_Player_Position(game, game.Get_Player().position.x, game.Get_Player().position.y, move.x, move.y, game.Get_Player().def.species);
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
