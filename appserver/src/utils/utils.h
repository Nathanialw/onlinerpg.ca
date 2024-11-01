#pragma once

//
// Created by nathanial on 3/29/24.
//

#ifndef BROWSERRPG_UTILS_H
#define BROWSERRPG_UTILS_H

#endif //BROWSERRPG_UTILS_H

namespace Utils {
     std::string uint16ToChars(uint16_t value);

     uint16_t charsToUint16(const std::string &str);

     std::string Prepend_Zero(int num);

     std::string Prepend_Zero_3Digit(int num);

     std::string Prepend_Zero_By_Digits(int num, int numDigits);

     std::string Prepend_Zero_By_Digits(size_t num, int numDigits);

     int8_t Add(int8_t a, int8_t b);

     uint8_t Add(const uint8_t &a, const uint8_t &b);

     int Add(int a, int b);

     int Random(int min, int max);

     float Random(float min, float max);
}