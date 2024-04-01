#pragma once
#include <cstdint>
#include <span>

struct RGB {
  uint8_t r;
  uint8_t g;
  uint8_t b;

  constexpr std::span<uint8_t> as_span() {
    return {&r, 3};
  }

  constexpr RGB dim() const {
    return {
        static_cast<uint8_t>(r >> 1),
        static_cast<uint8_t>(g >> 1),
        static_cast<uint8_t>(b >> 1),
    };
  }
};
