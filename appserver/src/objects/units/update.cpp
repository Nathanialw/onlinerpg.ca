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

  std::unordered_map<char, Component::Position> updatePosition = {
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
        game.objects[game.level][game.location].units[0] = game.objects[level][location].units[0];
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
            if (Attack::Check_For_Target(unit.position, game.Get_Player().position)) {
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

                int attackerIndex = Units::Get_Unit_Index(game.objects[unit.level][unit.location].unitPositions, unit.position.x, unit.position.y);
                auto &attacker = game.objects[unit.level][unit.location].units[attackerIndex];

                auto targetLocation = Attack::Check_Target_Location(attacker, moveTo);
                auto &targetList = game.objects[game.Get_Player().level][targetLocation];
                auto defaultChunk = game.map[game.Get_Player().level][targetLocation].defaultChunk;
                auto targetChunk = game.map[game.Get_Player().level][targetLocation].chunk;

                auto melee = Attack::Melee(attacker, targetList, defaultChunk, targetChunk, unit.position.x, unit.position.y, moveTo.x, moveTo.y);
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
    
//    std::cout << "Drawing map start: "<< std::endl;
//    for (int i = 0; i < Component::mapWidth; i++) {
//      std::cout << mapString.substr(i * Component::mapWidth, Component::mapWidth) << std::endl;
//    }
//    std::cout << "Drawing map end: "<< std::endl;
  }

  std::string Update_Player(Game::State &game, const char *direction) {
    auto move = updatePosition[*direction];

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
    int attackerIndex = Units::Get_Unit_Index(game.objects[game.Get_Player().level][game.Get_Player().location].unitPositions, game.Get_Player().position.x, game.Get_Player().position.y);
    auto &attacker = game.objects[game.Get_Player().level][game.Get_Player().location].units[attackerIndex];

    auto targetLocation = Attack::Check_Target_Location(attacker, move);
    auto &targetList = game.objects[game.Get_Player().level][targetLocation];
    auto &defaultChunk = game.map[game.Get_Player().level][targetLocation].defaultChunk;
    auto &targetChunk = game.map[game.Get_Player().level][targetLocation].chunk;

    auto melee = Attack::Melee(attacker, targetList, defaultChunk, targetChunk, game.Get_Player().position.x, game.Get_Player().position.y, move.x, move.y);
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
