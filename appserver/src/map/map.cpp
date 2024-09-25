//
// Created by nathanial on 3/29/24.
//
#include "string"

#include "map.h"
#include "labyrinth.h"

namespace Map {

  const int mapWidth = 99;
  std::string defaultMap[mapWidth][mapWidth];
  std::string gameMap[mapWidth][mapWidth];

  std::string Get_Map() {
    std::string map;
    for (int j = 0; j < mapWidth; j++) {
      for (int i = 0; i < mapWidth; i++) {
        if (i < 0 || i > mapWidth || j < 0 || j > mapWidth)
          map += ' ';
        else
          map += gameMap[j][i];
      }
    }
    return map;
  }

  void Set_Game_Map() {
    for (int x = 0; x < mapWidth; x++) {
      for (int y = 0; y < mapWidth; y++) {
        gameMap[x][y] = defaultMap[x][y];
      }
    }
  }

  void Create_Open_Map() {
    for (int i = 0; i < mapWidth; i++) {
      for (int j = 0; j < mapWidth; j++) {
        if (i == 0 || i == mapWidth - 1 || j == 0 || j == mapWidth - 1) {
          defaultMap[i][j] = '#';
          gameMap[i][j] = defaultMap[i][j];
        } else {
          defaultMap[i][j] = '.';
          gameMap[i][j] = defaultMap[i][j];
        }
      }
    }
  }

  void Create_Labyrinth() {
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
            defaultMap[x][y] = labyrinthStr[charIndex];
            charIndex++;
          }
        }
      }
    }
  }

  //3x3 rooms = quarters
  //9x9 rooms = barracks
  //9x15 rooms = halls
  void Add_Room(int x, int y, int w, int h, bool columns = false) {
    std::cout << "Adding room at: " << x << ", " << y << std::endl;
    for (int k = 0; k < w; k++) {
      for (int l = 0; l < h; l++) {
        int j = x + l;
        int i = y + k;
        defaultMap[j][i] = ".";
        if (columns && l & 5 && k & 4) {
          defaultMap[i][j] = "#";
        }

      }
    }
  }

  void Add_Rooms() {
    Add_Room(2, 2, 3, 3);
    Add_Room(4, 7, 9, 9);
    Add_Room(2, 19, 9, 16, true);
    Add_Room(3, 55, 5, 5);
  }

  std::string Init() {
    std::cout << "Creating labyrinth" << std::endl;
    Create_Labyrinth();
    std::cout << "Adding rooms" << std::endl;
    Add_Rooms();
    std::cout << "Setting open map" << std::endl;
    Set_Game_Map();

    auto map = Get_Map();
    return map;
  }

  void Set_Tile(int x, int y, const std::string &tile) {
    gameMap[y][x] = tile;
  }

  void Reset_Tile(int x, int y) {
    gameMap[y][x] = defaultMap[y][x];
  }

  void Update(int px, int py, int x, int y, const std::string &tile) {
    Reset_Tile(px, py);
    Set_Tile(px + x, py + y, tile);
  }

  // state 1 = initial map, 2 = update map
  std::string SendMapSegment(const Units::Unit &player, const std::string& direction, int state) {
    std::string mapSegment = std::to_string(state);
    mapSegment += std::to_string((player.vision * 2) + 1);
    mapSegment += direction;

    for (int j = player.position.y - player.vision; j <= player.position.y + player.vision; j++) {
        for (int i = player.position.x - player.vision; i <= player.position.x + player.vision; i++) {
            if (i < 0 || i >= mapWidth || j < 0 || j >= mapWidth)
              mapSegment += ' ';
            else
              mapSegment += gameMap[j][i];
        }
    }

    return mapSegment;
  }

  std::string Get_Adjacent_Tile(int x, int y) {
    std::string tile;
    if (x < 0 || x >= mapWidth || y < 0 || y >= mapWidth)
        tile = " ";
    else
        tile = gameMap[y][x];
    return tile;
  }
}