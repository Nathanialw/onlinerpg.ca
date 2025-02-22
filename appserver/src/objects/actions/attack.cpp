//
// Created by desktop on 9/14/24.
//
#include "attack.h"
#include "iostream"
#include "map.h"
#include "spawn.h"
#include "utils.h"

namespace Attack {

     Component::Position Check_Target_Location(const Unit::Unit &unit, const Component::Position &moveTo) {
	     auto location = unit.position.location;
	     auto target = unit.position.position.Add(moveTo);
	     if (target.x < 0) {
		     location.x--;
	     } else if (target.x >= Component::mapWidth) {
		     location.x++;
	     } else if (target.y < 0) {
		     location.y--;
	     } else if (target.y >= Component::mapWidth) {
		     location.y++;
	     }
	     return location;
     }

     int Check_Target(Units::Objects &targets, Component::Position &position, Component::Position &moveTo) {
	     //if at the edge of the map
	     int targetIndex;

	     if (position.x + moveTo.x < 0) {
		     Component::Position newPos = {Component::mapWidth - 1, Utils::Add(position.y, moveTo.y)};
		     targetIndex = Units::Get_Unit_Index(targets.unitPositions, newPos);
	     } else if (position.x + moveTo.x >= Component::mapWidth) {
		     Component::Position newPos = {0, Utils::Add(position.y, moveTo.y)};
		     targetIndex = Units::Get_Unit_Index(targets.unitPositions, newPos);
	     } else if (position.y + moveTo.y < 0) {
		     Component::Position newPos = {Utils::Add(position.x, moveTo.x), Component::mapWidth - 1};
		     targetIndex = Units::Get_Unit_Index(targets.unitPositions, newPos);
	     } else if (position.y + moveTo.y >= Component::mapWidth) {
		     Component::Position newPos = {Utils::Add(position.x, moveTo.x), 0};
		     targetIndex = Units::Get_Unit_Index(targets.unitPositions, newPos);
	     } else {
		     targetIndex = Units::Get_Unit_Index(targets.unitPositions, position.Add(moveTo));
	     }
	     return targetIndex;
     }

     //needs the correct objects list of the attacker
     //needs the correct objects list of the target
     //needs the correct chunk/defaultChunk of the target
     //then grab the index of the attacker
     //then grab the index of the target
     //which may be in a different chunk
     Damage Melee(Unit::Unit &attacker, Units::Objects &targets, Chunk::Chunk chunk, Component::Position &position, Component::Position &moveTo) {
	     auto targetIndex = Check_Target(targets, position, moveTo);
	     Damage target;

	     if (targetIndex == -1) {
		     std::cout << "no target found" << std::endl;
		     return target;
	     }

	     std::cout << "attacking: " << targetIndex << std::endl;
	     auto &targetUnit = targets.units[targetIndex];

	     target.target = Utils::Prepend_Zero_By_Digits((int) targetUnit.def.species, 2);
	     target.damageDone = Utils::Random(attacker.stats.minDamage, attacker.stats.maxDamage);
	     target.targetExists = true;

	     //TODO: //need to add the AC of the target to the damage calculation
	     if (targetUnit.stats.health > target.damageDone) {
		     targetUnit.stats.health -= target.damageDone;
		     std::cout << Spawn::Get_Unit_Char(attacker.def.species) << " has attacked a: " << Spawn::Get_Unit_Char(targetUnit.def.species) << " for " << (int) target.damageDone << " damage, " << (int) targetUnit.stats.health << " health remaining" << std::endl;
		     std::cout << "species: " << (int) targetUnit.def.species << std::endl;
		     return target;
	     }

	     attacker.stats.xp.Add_XP(targetUnit.stats.xp.Value());
	     targetUnit.stats.health = 0;
	     std::cout << "target dead" << std::endl;
	     Units::Remove_Unit(targets.unitPositions, targets.emptyUnitSlots, position.Add(moveTo));
	     chunk[position.y + moveTo.y][position.x + moveTo.x] = ',';
	     target.isDead = true;
	     return target;
     }

     bool Check_For_Target(const Component::Position &position, const Component::Position &target, uint8_t visionRange) {
	     //if visionrange.x < position
	     //      check the chunk to the right
	     //if visionrange.y < position
	     //      check the chunk to the below
	     //    if visionrange.x > position
	     //          check the chunk to the left
	     //    if visionrange.y > position
	     //          check the chunk to the above

	     if (abs(position.x - target.x) < visionRange && abs(position.y - target.y) < visionRange)
		     return true;
	     return false;
     }

     void Check_For_Target_On_Map_Chunk(const Component::Position &position, const Component::Position &target) {
	     //only one of these can be true
	     //need to create a temporary pathing map that merges the map chunks
	     //corner cases merge 4 map chunks
	     //edge cases merge 2 map chunks, unless close to the corner, then merge 4

	     if (target.x < 0 && target.y < 0) {
		     //target is on the top left map chunk
	     } else if (target.x >= Component::mapWidth && target.y < 0) {
		     //target is on the top right map chunk
	     } else if (target.x < 0 && target.y >= Component::mapWidth) {
		     //target is on the bottom left map chunk
	     } else if (target.x >= Component::mapWidth && target.y >= Component::mapWidth) {
		     //target is on the bottom right map chunk
	     } else if (target.x < 0) {
		     //target is on the left map chunk
	     } else if (target.x >= Component::mapWidth) {
		     //target is on the right map chunk
	     } else if (target.y < 0) {
		     //target is on the top map chunk
	     } else if (target.y >= Component::mapWidth) {
		     //target is on the bottom map chunk
	     }
     }

     std::string As_Sendable_String(const Damage &damage) {
	     return damage.target + Utils::Prepend_Zero_By_Digits(damage.damageDone, 2) + std::to_string(damage.isDead);
     }

}