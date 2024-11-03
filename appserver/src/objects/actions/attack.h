#pragma once

#include "string"
#include "game.h"

namespace Attack {
     struct Damage {
	std::string target = "";
	int damageDone = 0;
	bool isDead = false;
	bool targetExists = false;
     };

     Damage Melee(Unit::Unit &attacker, Units::Objects &targets, Chunk::Chunk chunk, Component::Position &position, Component::Position &moveTo);

     Component::Position Check_Target_Location(const Unit::Unit &unit, const Component::Position &moveTo);

     bool Check_For_Target(const Component::Position &position, const Component::Position &target, uint8_t visionRange);

     std::string As_Sendable_String(const Damage &damage);
}