#pragma once
#include <avr/io.h>

namespace ADC {
inline void Enable() {
  ADC0.CTRLA = ADC_ENABLE_bm;
}

inline void Select(uint8_t analog_input) {
  ADC0.MUXPOS = analog_input;
}

inline void Start() {
  ADC0.COMMAND = ADC_STCONV_bm;
}

inline bool ResultReady() {
  return ADC0.INTFLAGS & ADC_RESRDY_bm;
}

constexpr uint16_t min() {
  return 0;
}

constexpr uint16_t max() {
  return 0xFFF;  // 12bit max
}
};  // namespace ADC
