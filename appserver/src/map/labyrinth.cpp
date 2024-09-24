//
// Created by nathanial on 3/29/24.
//
#include "string"
#include "stack"
#include "array"
#include "vector"

#include "labyrinth.h"
#include "procgen.h"


namespace Labyrinth {
  std::array<std::string, 15> mapCells =
    {
        ".........",
        "####.##.#",
        "#.##..#.#",
        "###...###",
        "#.#..##.#",
        "#.##.####",
        "#.##..###",
        "####..#.#",
        "#.#..####",
        "###..##.#",
        "####..###",
        "#.##.##.#",
        "###..####",
        "#.#...###",
        "###...#.#",
    };

  int m_nMazeWidth;
  int m_nMazeHeight;
  std::array<int, mapWidth * mapWidth> m_maze;
  std::array<int, mapWidth * mapWidth> labyrinth;
  int m_nVisitedCells;
  std::stack<std::pair<int, int>> m_stack;// (x, y) coordinate pairs
  Proc_Gen::Seed seed;

  // Some bit fields for convenience
  enum {
    CELL_PATH_N = 0x01,
    CELL_PATH_E = 0x02,
    CELL_PATH_S = 0x04,
    CELL_PATH_W = 0x08,
    CELL_VISITED = 0x10,
  };

  bool Generate_Map() {

    auto offset = [&](int x, int y) {
      return (m_stack.top().second + y) * m_nMazeWidth + (m_stack.top().first + x);
    };

    while (m_nVisitedCells < m_nMazeWidth * m_nMazeHeight) {
      // Create a set of unvisited neighbours
      std::vector<int> neighbours;

      // North
      if (m_stack.top().second > 0 && (m_maze[offset(0, -1)] & CELL_VISITED) == 0)
        neighbours.push_back(0);
      // East
      if (m_stack.top().first < m_nMazeWidth - 1 && (m_maze[offset(1, 0)] & CELL_VISITED) == 0)
        neighbours.push_back(1);
      // South
      if (m_stack.top().second < m_nMazeHeight - 1 && (m_maze[offset(0, 1)] & CELL_VISITED) == 0)
        neighbours.push_back(2);
      // West
      if (m_stack.top().first > 0 && (m_maze[offset(-1, 0)] & CELL_VISITED) == 0)
        neighbours.push_back(3);

      // Are there any neighbours available?
      if (!neighbours.empty()) {
        // change to procedural!
        int next_cell_dir = neighbours[Proc_Gen::Random_Int(0, neighbours.size(), seed)];

        // Create a path between the neighbour and the current cell
        switch (next_cell_dir) {
        case 0:// North
          m_maze[offset(0, -1)] |= CELL_VISITED | CELL_PATH_S;
          m_maze[offset(0, 0)] |= CELL_PATH_N;
          m_stack.emplace((m_stack.top().first + 0), (m_stack.top().second - 1));
          break;

        case 1:// East
          m_maze[offset(+1, 0)] |= CELL_VISITED | CELL_PATH_W;
          m_maze[offset(0, 0)] |= CELL_PATH_E;
          m_stack.emplace((m_stack.top().first + 1), (m_stack.top().second + 0));
          break;

        case 2:// South
          m_maze[offset(0, +1)] |= CELL_VISITED | CELL_PATH_N;
          m_maze[offset(0, 0)] |= CELL_PATH_S;
          m_stack.emplace((m_stack.top().first + 0), (m_stack.top().second + 1));
          break;

        case 3:// West
          m_maze[offset(-1, 0)] |= CELL_VISITED | CELL_PATH_E;
          m_maze[offset(0, 0)] |= CELL_PATH_W;
          m_stack.emplace((m_stack.top().first - 1), (m_stack.top().second + 0));
          break;
        }

        m_nVisitedCells++;
      } else {
        // No available neighbours so backtrack!
        m_stack.pop();
      }
    }

    for (int x = 0; x < m_nMazeWidth; x++) {
      for (int y = 0; y < m_nMazeHeight; y++) {
        labyrinth[y * m_nMazeWidth + x] = m_maze[y * m_nMazeWidth + x] -= 17;
      }
    }
    return true;
  }


  std::string Create_Map() {
    std::string labyrinthStr;
//    std::string labyrinth[mapWidth][mapWidth];
//
//    for (int i = 0; i < mapWidth; i++) {
//      for (int j = 0; j < mapWidth; j++) {
//        if (i == 0 || i == mapWidth - 1 || j == 0 || j == mapWidth - 1) {
//          labyrinth[i][j] = '#';
//          labyrinthStr += labyrinth[i][j];
//        }
//        else {
//          labyrinth[i][j] = '.';
//          labyrinthStr += labyrinth[i][j];
//        }
//      }
//    }

    return labyrinthStr;
  }

}