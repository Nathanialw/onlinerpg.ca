//
// Created by desktop on 9/21/24.
//
#include <array>
#include <vector>
#include <list>
#include "math.h"

#include "pathing.h"
#include "components.h"
#include "iostream"

namespace Pathing {

  constexpr int REGION_SIZE = 100;

  struct sNode {
    bool bObstacle = false;
    bool bVisited = false;
    float fGlobalGoal{};
    float fLocalGoal{};
    // position
    int x{};
    int y{};
    std::vector<sNode *> vecNeighbours;
    sNode *parent{};
  };

  constexpr int nMapWidth = REGION_SIZE;
  constexpr int nMapHeight = REGION_SIZE;

  std::array<sNode, nMapWidth * nMapHeight> nodes;

  sNode *nodeStart = nullptr;
  sNode *nodeEnd = nullptr;

  // clear previous location, set new location
  void Update(const std::string &mapString) {
      for (int x = 0; x < nMapWidth; x++) {
        for (int y = 0; y < nMapHeight; y++) {
          if (mapString[y * nMapWidth + x] == '.') {
            nodes[y * nMapWidth + x].bObstacle = false;
          }
          else {
            nodes[y * nMapWidth + x].bObstacle = true;
          }
        }
      }
  }

  bool Init(const std::string &mapString) {
    for (int x = 0; x < nMapWidth; x++) {
      for (int y = 0; y < nMapHeight; y++) {
        nodes[y * nMapWidth + x].x = x;
        nodes[y * nMapWidth + x].y = y;
        nodes[y * nMapWidth + x].bObstacle = true;
        nodes[y * nMapWidth + x].parent = nullptr;
        nodes[y * nMapWidth + x].bVisited = false;
        nodes[y * nMapWidth + x].vecNeighbours.clear();
      }
    }

    for (int x = 0; x < nMapWidth; x++)
      for (int y = 0; y < nMapHeight; y++) {
        if (y > 0)
          nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x + 0)]);
        if (y < nMapHeight - 1)
          nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x + 0)]);
        if (x > 0)
          nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * nMapWidth + (x - 1)]);
        if (x < nMapWidth - 1)
          nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * nMapWidth + (x + 1)]);
        }

    // Manually position the start and end markers so they are not nullptr
    nodeStart = &nodes[(nMapHeight / 2) * nMapWidth + 1];
    nodeEnd = &nodes[(nMapHeight / 2) * nMapWidth + nMapWidth - 2];

    Update(mapString);
    return true;
  }

  bool Solve_AStar(const Component::Position &position, const Component::Position &target, std::vector<Component::Position> &path) {

    // Reset Navigation Graph - default all node states
    nodeStart = &nodes[(position.y * nMapWidth) + position.x];
    nodeEnd = &nodes[(target.y * nMapWidth) + target.x];

    int numCellsToCheck;
//    (nodeEnd->bObstacle) ? numCellsToCheck = 1 : numCellsToCheck = 10000;
    numCellsToCheck = 10000;

    for (int x = 0; x < nMapWidth; x++)
      for (int y = 0; y < nMapHeight; y++) {
        nodes[y * nMapWidth + x].bVisited = false;
        nodes[y * nMapWidth + x].fGlobalGoal = INFINITY;
        nodes[y * nMapWidth + x].fLocalGoal = INFINITY;
        nodes[y * nMapWidth + x].parent = nullptr;// No parents
      }

    auto distance = [](sNode *a, sNode *b)// For convenience
    {
      return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
    };

    auto heuristic = [distance](sNode *a, sNode *b)// So we can experiment with heuristic
    {
      return distance(a, b);
    };

    // Setup starting conditions
    sNode *nodeCurrent = nodeStart;
    nodeStart->fLocalGoal = 0.0f;
    nodeStart->fGlobalGoal = heuristic(nodeStart, nodeEnd);

    // Add start node to not tested list - this will ensure it gets tested.
    // As the algorithm progresses, newly discovered nodes get added to this
    // list, and will themselves be tested later
    std::list<sNode *> listNotTestedNodes;
    listNotTestedNodes.push_back(nodeStart);

    // if the not tested list contains nodes, there may be better paths
    // which have not yet been explored. However, we will also stop
    // searching when we reach the target - there may well be better
    // paths but this one will do - it wont be the longest.
    int i = 0;
    while (!listNotTestedNodes.empty() && nodeCurrent != nodeEnd)// Find absolutely shortest path // && nodeCurrent != nodeEnd)
    {
      if (i > numCellsToCheck) {
        sNode *k = nodeCurrent;
        while (k != nodeStart) {
          Component::Position cell = {k->x, k->y};
          path.emplace_back(cell);
          k = k->parent;
          if (k == nullptr) return false;
        }
        return false;
      }
      i++;
      // Sort Untested nodes by global goal, so lowest is first
      listNotTestedNodes.sort([](const sNode *lhs, const sNode *rhs) { return lhs->fGlobalGoal < rhs->fGlobalGoal; });

      // Front of listNotTestedNodes is potentially the lowest distance node. Our
      // list may also contain nodes that have been visited, so ditch these...
      while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
        listNotTestedNodes.pop_front();

      // ...or abort because there are no valid nodes left to test
      if (listNotTestedNodes.empty())
        break;

      nodeCurrent = listNotTestedNodes.front();
      nodeCurrent->bVisited = true;// We only explore a node once


      // Check each of this node's neighbours...
      for (auto nodeNeighbour: nodeCurrent->vecNeighbours) {
        // ... and only if the neighbour is not visited and is
        // not an obstacle, add it to NotTested List
        if (!nodeNeighbour->bVisited && nodeNeighbour->bObstacle == 0)
          listNotTestedNodes.push_back(nodeNeighbour);

        // Calculate the neighbours potential lowest parent distance
        float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + distance(nodeCurrent, nodeNeighbour);

        // If choosing to path through this node is a lower distance than what
        // the neighbour currently has set, update the neighbour to use this node
        // as the path source, and set its distance scores as necessary
        if (fPossiblyLowerGoal < nodeNeighbour->fLocalGoal) {
          nodeNeighbour->parent = nodeCurrent;
          nodeNeighbour->fLocalGoal = fPossiblyLowerGoal;

          // The best path length to the neighbour being tested has changed, so
          // update the neighbour's score. The heuristic is used to globally bias
          // the path algorithm, so it knows if its getting better or worse. At some
          // point the algo will realise this path is worse and abandon it, and then go
          // and search along the next best path.
          nodeNeighbour->fGlobalGoal = nodeNeighbour->fLocalGoal + heuristic(nodeNeighbour, nodeEnd);
        }
      }
    }

    sNode *k = nodeEnd;
    while (k != nodeStart) {
      path.push_back({k->x, k->y});
      k = k->parent;
      if (k == nullptr) break;
    }

    return true;
  }

  Component::Position Move_To(Component::Position &position, const Component::Position &targetPosition) {
    //auto pathing = zone.emplace_or_replace<Component::Pathing>(entity_ID);
    std::vector<Component::Position> path = {};
    Solve_AStar(position, targetPosition, path);
    for (auto & i : path)
        std::cout << "path: " << i.x << " " << i.y << std::endl;


    if (path.empty() || path.size() <= 1) {
      std::cout << "position: " << position.x << " " << position.y << " " << "target: " << targetPosition.x << " " << targetPosition.y << std::endl;
      return {targetPosition.x - position.x, targetPosition.y - position.y};
    }
    int cell = 1;

    std::cout << "position: " << position.x << " " << position.y << " " << "target: " << path[path.size() - cell].x << " " << path[path.size() - cell].y << std::endl;
    return {path[path.size() - cell].x - position.x, path[path.size() - cell].y - position.y};
  }
}
