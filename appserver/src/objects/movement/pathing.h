#pragma once

#include "components.h"
#include "string"

//
// Created by desktop on 9/21/24.
//


namespace Pathing {
     typedef Component::sNode Map[Component::mapWidth * Component::mapWidth];

     void Connect_Chunks(Map chunk, Map newChunk, int x, int y);

     Component::Position Move_To(Map nodes, Component::Position &position, const Component::Position &targetPosition);

     bool Init(Map nodes, const std::string &mapString);

     void Update(Map nodes, const std::string &mapString);
}
