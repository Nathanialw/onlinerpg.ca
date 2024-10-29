//
// Created by nathanial on 3/29/24.
//
#include <cstdint>
#include "string"
#include "utils.h"
#include "random"

namespace Utils {

     std::string uint16ToChars(uint16_t value) {
	     char highByte = (value & 0xFF00) >> 8;
	     char lowByte = value & 0x00FF;
	     return std::string(1, highByte) + std::string(1, lowByte);
     }

     uint16_t charsToUint16(const std::string &str) {
	     uint16_t highByte = static_cast<uint16_t>(str[0]) << 8;
	     uint16_t lowByte = static_cast<uint16_t>(str[1]);
	     return highByte | lowByte;
     }

     std::string Prepend_Zero(int num) {
	     std::string str = std::to_string(num);
	     if (num < 10)
		     str = "0" + str;
	     return str;
     }

     std::string Prepend_Zero_3Digit(int num) {
	     std::string str = std::to_string(num);
	     if (num < 10)
		     str = "00" + str;
	     else if (num < 100)
		     str = "0" + str;
	     return str;
     }

     std::string Prepend_Zero_By_Digits(int num, int numDigits) {
	     std::string str = std::to_string(num);
	     while (str.length() < numDigits) {
		     str = "0" + str;
	     }
	     return str;
     }

     int8_t Add(int8_t a, int8_t b) {
	     return a + b;
     }

     uint8_t Add(const uint8_t &a, const uint8_t &b) {
	     return a + b;
     }

     int Add(int a, int b) {
	     return a + b;
     }

     int Random(int min, int max) {
	     return min + (rand() % static_cast<int>(max - min + 1));
     }

     float Random(float min, float max) {
	     return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
     }
}

