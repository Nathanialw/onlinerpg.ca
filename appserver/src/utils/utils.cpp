//
// Created by nathanial on 3/29/24.
//
#include <cstdint>
#include "string"

#include "utils.h"

namespace Utils {

  std::string uint16ToChars(uint16_t value) {
    char highByte = (value & 0xFF00) >> 8;
    char lowByte = value & 0x00FF;
    return std::string(1, highByte) + std::string(1, lowByte);
  }

  uint16_t charsToUint16(const std::string& str) {
    uint16_t highByte = static_cast<uint16_t>(str[0]) << 8;
    uint16_t lowByte = static_cast<uint16_t>(str[1]);
    return highByte | lowByte;
  }
}