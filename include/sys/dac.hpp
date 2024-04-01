#pragma once
#include <avr/io.h>

namespace DAC {
inline void Enable() {
  // Enable both the peripheral and output on the Pin
  DAC0.CTRLA = DAC_OUTEN_bm | DAC_ENABLE_bm;
}

inline void Write(uint16_t data) {
  DAC0.DATA = data << 6;
}

constexpr uint16_t min() {
  return 0;
}

constexpr uint16_t max() {
  return 0x3FF;  // 10bit max
}
};  // namespace DAC
