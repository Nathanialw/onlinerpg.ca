//
// Created by nathanial on 3/29/24.
//
#include "string"

#include "game.h"
#include "map.h"
#include "labyrinth.h"
#include "procgen.h"

namespace Map {

  std::string Get_Map(Game::State &game) {
    std::string map;
    for (int j = 0; j < Component::mapWidth; j++) {
      for (int i = 0; i < Component::mapWidth; i++) {
        if (i < 0 || i > Component::mapWidth || j < 0 || j > Component::mapWidth)
          map += ' ';
        else
          map += game.gameMaps[game.location][j][i];
      }
    }
    return map;
  }

  void Set_Game_Map(Game::State &game) {
    for (int x = 0; x < Component::mapWidth; x++) {
      for (int y = 0; y < Component::mapWidth; y++) {
        game.gameMaps[game.location][x][y] = game.defaultMaps[game.location][x][y];
      }
    }
  }

  void Create_Open_Map(Game::State &game) {
    for (int i = 0; i < Component::mapWidth; i++) {
      for (int j = 0; j < Component::mapWidth; j++) {
        if (i == 0 || i == Component::mapWidth - 1 || j == 0 || j == Component::mapWidth - 1) {
          game.defaultMaps[game.location][i][j] = '#';
          game.gameMaps[game.location][i][j] = game.defaultMaps[game.location][i][j];
        } else {
          game.defaultMaps[game.location][i][j] = '.';
          game.gameMaps[game.location][i][j] = game.defaultMaps[game.location][i][j];
        }
      }
    }
  }

  void Create_Labyrinth(Game::State &game) {
    Labyrinth::Generate_Map();
    std::string labyrinthStr;
    const int cellSize = 3;

    for (int i = 0; i < Labyrinth::labyrinthWidth; i++) {
      for (int j = 0; j < Labyrinth::labyrinthWidth; j++) {
        labyrinthStr = Labyrinth::Get_Map_Cells() [Labyrinth::Get_Labyrinth()[j * Labyrinth::labyrinthWidth + i]];
        int charIndex = 0;
        if (i < 1 || j < 1)
          std::cout << "labyrinthStr: " << labyrinthStr << std::endl;

        for (int k = 0; k < cellSize; k++) {
          for (int l = 0; l < cellSize; l++) {
            int x = (i * cellSize) + k;
            int y = (j * cellSize) + l;
            game.defaultMaps[game.location][x][y] = labyrinthStr[charIndex];
            charIndex++;
          }
        }
      }
    }
  }

  //3x3 rooms = quarters
  //9x9 rooms = barracks
  //9x15 rooms = halls
  void Add_Room(Game::State &game, int x, int y, int w, int h, bool columns = false) {
    std::cout << "Adding room at: " << x << ", " << y << std::endl;
    for (int k = 0; k < w; k++) {
      for (int l = 0; l < h; l++) {
        int j = x + l;
        int i = y + k;
        game.defaultMaps[game.location][i][j] = '.';
      }
    }
  }

  void Add_Small_Rooms(Game::State &game) {
    Proc_Gen::Seed seed;
    for (int x = 1; x < Component::mapWidth - 7; x += 7) {
      for (int y = 1; y < Component::mapWidth - 7; y += 7) {
        seed.seed = Proc_Gen::Create_Initial_Seed(x, y);
        auto w = Proc_Gen::Random_Int(3, 6, seed);
        seed.seed = Proc_Gen::Create_Initial_Seed(y, x);
        int h = Proc_Gen::Random_Int(3, 6, seed);
        Add_Room(game, x, y, w, h);
      }
    }
//    Add_Room(2, 40, 9, 9);
//    Add_Room(12, 40, 9, 16);
//    Add_Room(30, 40, 5, 5);
  }
  std::vector<Room> largeRooms;

  std::vector<Room> Get_Large_Rooms() {
    return largeRooms;
  }

  void Add_Large_Rooms(Game::State &game) {
    Proc_Gen::Seed seed;
    for (int x = 1; x < (Component::mapWidth - 20); x+=21) {
      for (int y = 1; y < Component::mapWidth - 20; y+=21) {
        seed.seed = Proc_Gen::Create_Initial_Seed(x, y);
        auto w = Proc_Gen::Random_Int(9, 19, seed);
        seed.seed = Proc_Gen::Create_Initial_Seed(y, x);
        int h = Proc_Gen::Random_Int(9, 19, seed);
        Add_Room(game, x, y, w, h);
        largeRooms.push_back({x, y, w, h});
      }
    }
  }

  std::string Init(Game::State &game) {
//    std::cout << "Creating open map" << std::endl;
//    Create_Open_Map();
    std::cout << "Creating labyrinth" << std::endl;
    Create_Labyrinth(game);
    std::cout << "Adding rooms" << std::endl;
    Add_Small_Rooms(game);
    Add_Large_Rooms(game);
    std::cout << "Setting open map" << std::endl;
    Set_Game_Map(game);

    return Get_Map(game);
  }

  void Set_Tile(Game::State &game, int x, int y, const char &tile) {
    game.gameMaps[game.location][y][x] = tile;
  }

  void Reset_Tile(Game::State &game, int x, int y) {
    game.gameMaps[game.location][y][x] = game.defaultMaps[game.location][y][x];
  }

  void Update(Game::State &game, int px, int py, int x, int y, const char &tile) {
    Reset_Tile(game, px, py);
    Set_Tile(game, px + x, py + y, tile);
  }

  // state 1 = initial map, 2 = update map
  std::string SendMapSegment(Game::State &game, const std::string& direction, int state) {
    std::string mapSegment = std::to_string(state);
    auto &player = game.Get_Player();
    mapSegment += std::to_string((player.vision * 2) + 1);
    mapSegment += direction;

    for (int j = player.position.y - player.vision; j <= player.position.y + player.vision; j++) {
        for (int i = player.position.x - player.vision; i <= player.position.x + player.vision; i++) {
            if (i < 0 || i >= Component::mapWidth || j < 0 || j >= Component::mapWidth)
              mapSegment += ' ';
            else
              mapSegment += game.gameMaps[game.location][j][i];
        }
    }

    return mapSegment;
  }

  std::string Get_Adjacent_Tile(Game::State &game, int x, int y) {
    std::string tile;
    if (x < 0 || x >= Component::mapWidth || y < 0 || y >= Component::mapWidth)
        tile = " ";
    else
        tile = game.gameMaps[game.location][y][x];
    return tile;
  }
}