//
// Created by desktop on 11/2/24.
//

#include "xp.h"
#include "utils.h"
#include "iostream"

void XP::Level_Up(uint16_t xp) {
//	=FLOOR(SUM(prev+(prev * 0.040922) , 50)) where cell 1 = 100
	xp -= (xpToLevel - xpCurrent); //ensures no overflow
	xpToLevel = (xpToLevel + (xpToLevel * 0.040922)) + 50;
	xpCurrent = xp;
	std::cout << "level: " << (int)level << " xpCurrent: " << xpCurrent << " xpToLevel: " << xpToLevel << std::endl;
	level++;
	std::cout << "level: " << (int)level << " xpCurrent: " << xpCurrent << " xpToLevel: " << xpToLevel << std::endl;
};

void XP::Add_XP(uint16_t xp) {
	std::cout << "xpCurrent: " << xpCurrent << " xpToLevel: " << xpToLevel << std::endl;
	if ((xpCurrent + xp) >= xpToLevel) {
		std::cout << "level up" << std::endl;
		Level_Up(xp);
	} else {
		xpCurrent += xp;
		std::cout << "xpCurrent: " << xpCurrent << " xpToLevel: " << xpToLevel << std::endl;
	}
}


//TODO: implement XP based on kill value
uint16_t XP::Value() const {
	return 40;
}

std::string XP::As_Sendable_String() const {
	std::cout << "level: " << (int)level << " xpCurrent: " << xpCurrent << " xpToLevel: " << xpToLevel << std::endl;
	auto percent = (uint16_t)(((float)xpCurrent / (float)xpToLevel) * 100);
	std::cout << "percent: " << percent << "calc: " << (xpCurrent / xpToLevel) << "x100" << (xpCurrent / xpToLevel) * 100 << std::endl;
	return Utils::Prepend_Zero_By_Digits(level, 2) + Utils::Prepend_Zero_By_Digits(percent, 2);
}