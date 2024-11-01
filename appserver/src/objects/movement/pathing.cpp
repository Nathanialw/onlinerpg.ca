//
// Created by desktop on 9/21/24.
//
#include <vector>
#include <list>
#include <cmath>

#include "pathing.h"
#include "components.h"
#include "iostream"

namespace Pathing {

//  std::array<sNode, nMapWidth * nMapHeight> nodes;



     // clear previous location, set new location
     void Update(Map nodes, const std::string &mapString) {
	     for (size_t y = 0; y < Component::mapWidth; y++) {
		     for (size_t x = 0; x < Component::mapWidth; x++) {
			     if (mapString[y * Component::mapWidth + x] == '.') {
				     nodes[y * Component::mapWidth + x].bObstacle = false;
			     } else {
				     nodes[y * Component::mapWidth + x].bObstacle = true;
			     }
		     }
	     }
     }

     void Draw_Collision_Map(Map nodes) {
	     std::cout << "Drawing collision map: " << std::endl;
	     for (size_t y = 0; y < Component::mapWidth; y++) {
		     for (size_t x = 0; x < Component::mapWidth; x++) {
			     if (nodes[y * Component::mapWidth + x].bObstacle) {
				     std::cout << "#";
			     } else {
				     std::cout << ".";
			     }
		     }
		     std::cout << std::endl;
	     }
     }

     bool Init(Map nodes, const std::string &mapString) {
	     for (size_t y = 0; y < Component::mapWidth; y++) {
		     for (size_t x = 0; x < Component::mapWidth; x++) {
			     nodes[y * Component::mapWidth + x].x = x;
			     nodes[y * Component::mapWidth + x].y = y;
			     nodes[y * Component::mapWidth + x].bObstacle = true;
			     nodes[y * Component::mapWidth + x].parent = nullptr;
			     nodes[y * Component::mapWidth + x].bVisited = false;
			     nodes[y * Component::mapWidth + x].vecNeighbours.clear();
		     }
	     }

	     for (size_t y = 0; y < Component::mapWidth; y++)
		     for (size_t x = 0; x < Component::mapWidth; x++) {
			     if (y > 0)
				     nodes[y * Component::mapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * Component::mapWidth + (x + 0)]);
			     if (y < Component::mapWidth - 1)
				     nodes[y * Component::mapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * Component::mapWidth + (x + 0)]);
			     if (x > 0)
				     nodes[y * Component::mapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * Component::mapWidth + (x - 1)]);
			     if (x < Component::mapWidth - 1)
				     nodes[y * Component::mapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * Component::mapWidth + (x + 1)]);
		     }

	     // Manually position the start and end markers, so they are not nullptr
//    nodeStart = &nodes[(Component::mapWidth / 2) * Component::mapWidth + 1];
//    nodeEnd = &nodes[(Component::mapWidth / 2) * Component::mapWidth + Component::mapWidth - 2];

	     Update(nodes, mapString);
	     Draw_Collision_Map(nodes);
	     std::cout << "path inited" << std::endl;
	     return true;
     }

     bool Solve_AStar(Map nodes, const Component::Position &position, const Component::Position &target, std::vector<Component::Position> &path) {
	     ///need location AND position
	     ///needs to be able to search off the map  into the location of the target + the 2 adjecent chunks


	     // Reset Navigation Graph - default all node states
	     Component::sNode *nodeStart = &nodes[(position.y * Component::mapWidth) + position.x];
	     Component::sNode *nodeEnd = &nodes[(target.y * Component::mapWidth) + target.x];

	     int numCellsToCheck;
//    (nodeEnd->bObstacle) ? numCellsToCheck = 1 : numCellsToCheck = 10000;
	     numCellsToCheck = 10000;

	     for (Component::PosInt x = 0; x < Component::mapWidth; x++)
		     for (Component::PosInt y = 0; y < Component::mapWidth; y++) {
			     nodes[y * Component::mapWidth + x].bVisited = false;
			     nodes[y * Component::mapWidth + x].fGlobalGoal = INFINITY;
			     nodes[y * Component::mapWidth + x].fLocalGoal = INFINITY;
			     nodes[y * Component::mapWidth + x].parent = nullptr;// No parents
		     }

	     auto distance = [](Component::sNode *a, Component::sNode *b)// For convenience
	     {
		return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
	     };

	     auto heuristic = [distance](Component::sNode *a, Component::sNode *b)// So we can experiment with heuristic
	     {
		return distance(a, b);
	     };

	     // Setup starting conditions
	     Component::sNode *nodeCurrent = nodeStart;
	     nodeStart->fLocalGoal = 0.0f;
	     nodeStart->fGlobalGoal = heuristic(nodeStart, nodeEnd);

	     // Add start node to not tested list - this will ensure it gets tested.
	     // As the algorithm progresses, newly discovered nodes get added to this
	     // list, and will themselves be tested later
	     std::list<Component::sNode *> listNotTestedNodes;
	     listNotTestedNodes.push_back(nodeStart);

	     // if the not tested list contains nodes, there may be better paths
	     // which have not yet been explored. However, we will also stop
	     // searching when we reach the target - there may well be better
	     // paths but this one will do - it won't be the longest.
	     int i = 0;
	     while (!listNotTestedNodes.empty() && nodeCurrent != nodeEnd)// Find absolute shortest path // && nodeCurrent != nodeEnd)
	     {
		     if (i > numCellsToCheck) {
			     Component::sNode *k = nodeCurrent;
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
		     listNotTestedNodes.sort([](const Component::sNode *lhs, const Component::sNode *rhs) { return lhs->fGlobalGoal < rhs->fGlobalGoal; });

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

	     Component::sNode *k = nodeEnd;
	     while (k != nodeStart) {
		     path.push_back({k->x, k->y});
		     k = k->parent;
		     if (k == nullptr) break;
	     }

	     return true;
     }

     void Connect_Chunks(Pathing::Map chunk, Pathing::Map toConnect, int x, int y) {
	     //mutually connect the chunks
//    if (x == -1) {
//      //connect left
//      for (int i = 0; i < Component::mapWidth * Component::mapWidth; i += Component::mapWidth) {
//        std::cout << "i: " << i << std::endl;
//        std::cout << "i + Component::mapWidth - 1: " << i + Component::mapWidth - 1 << std::endl;
//        std::cout << "total mapSize: " << Component::mapWidth * Component::mapWidth << std::endl;
//          chunk[i].vecNeighbours.push_back(&toConnect[i + Component::mapWidth - 1]);
//          toConnect[i + Component::mapWidth - 1].vecNeighbours.push_back(&chunk[i]);
//      }
//      std::cout << "connected left" << std::endl;
//    }
	     if (x == 1) {
		     //connect right
		     for (size_t i = Component::mapWidth - 1; i < Component::mapWidth * Component::mapWidth; i += Component::mapWidth) {
			     std::cout << "i: " << i << std::endl;
			     std::cout << "i - (Component::mapWidth - 1): " << i - (Component::mapWidth - 1) << std::endl;

			     chunk[i].vecNeighbours.push_back(&toConnect[i - (Component::mapWidth - 1)]);
			     toConnect[i - (Component::mapWidth - 1)].vecNeighbours.push_back(&chunk[i]);
		     }
		     std::cout << "connected right" << std::endl;
	     }
//    else if (y == -1) {
//      //connect up
//      for (int i = 0; i < Component::mapWidth; i++) {
//          std::cout << "i: " << i << std::endl;
//          std::cout << "((Component::mapWidth * Component::mapWidth) - Component::mapWidth) + i: " << ((Component::mapWidth * Component::mapWidth) - Component::mapWidth) + i << std::endl;
//          std::cout << "total mapSize: " << Component::mapWidth * Component::mapWidth << std::endl;
//          chunk[((Component::mapWidth * Component::mapWidth) - Component::mapWidth) + i].vecNeighbours.push_back(&toConnect[i]);
//          toConnect[i].vecNeighbours.push_back(&chunk[((Component::mapWidth * Component::mapWidth) - Component::mapWidth) + i]);
//      }
//      std::cout << "connected up" << std::endl;
//    }
//    else if (y == 1) {
//      //connect down
//      for (int i = 0; i < Component::mapWidth; i++) {
//          std::cout << "i: " << i << std::endl;
//          std::cout << "i - ((Component::mapWidth * Component::mapWidth) - Component::mapWidth): " << (Component::mapWidth * Component::mapWidth) - Component::mapWidth + i << std::endl;
//          std::cout << "total mapSize: " << Component::mapWidth * Component::mapWidth << std::endl;
//          chunk[i].vecNeighbours.push_back(&toConnect[(Component::mapWidth * Component::mapWidth) - Component::mapWidth + i]);
//          toConnect[(Component::mapWidth * Component::mapWidth) - Component::mapWidth + i].vecNeighbours.push_back(&chunk[i]);
//      }
//      std::cout << "connected down" << std::endl;
//    }
     }

     Component::Position Move_To(Map nodes, Component::Position &position, const Component::Position &targetPosition) {
	     std::vector<Component::Position> path = {};
	     Solve_AStar(nodes, position, targetPosition, path);

	     if (path.empty()) {
		     std::cout << "No path found" << std::endl;
		     return {0, 0};
	     }

	     int cell = 1;
	     std::cout << path.size() << std::endl;
	     std::cout << "moving toward target, position: " << position.As_String() << " next cell: " << path[path.size() - cell].As_String() << std::endl;
	     return {static_cast<Component::PosInt>((path[path.size() - cell].x - position.x)), static_cast<Component::PosInt>((path[path.size() - cell].y - position.y))};
     }
}
