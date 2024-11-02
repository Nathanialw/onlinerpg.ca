#pragma once
//
// Created by desktop on 11/2/24.
//
#include <cstdint>
#include "string"

class XP {
     uint16_t xpCurrent;
     uint16_t xpToLevel;
     uint8_t level = 1;

     void Level_Up(uint16_t xp) ;

     public:
     XP() {
	     xpCurrent = 0;
	     xpToLevel = 100;
	     level = 1;
     }

     void Add_XP(uint16_t xp);

     [[nodiscard]] uint16_t Value() const;

     [[nodiscard]] std::string As_Sendable_String() const;
};


