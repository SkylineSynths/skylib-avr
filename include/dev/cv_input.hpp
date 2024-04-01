#pragma once
#include <array>
#include <cassert>


#include "dev/pin.hpp"
#include "sys/dac.hpp"
#include "util/misc.hpp"
#include "util/rng.hpp"


class CVInput {
  static constexpr uint8_t kSequenceLength = 10;
  static constexpr std::array<uint16_t, kSequenceLength> sequence = {
      // 10600, 6658, 43502, 39924, 58740, 42088, 28296, 17073, 25043, 41793,
      558, 867, 679, 210, 316, 145, 498, 774, 300, 275,
  };

 public:
  CVInput(Pin pin) : pin_(pin) {
  }

  uint16_t Read() {
    idx_ = (idx_ - 1 + kSequenceLength) % kSequenceLength;
    // idx_ = (idx_ + 1) % kSequenceLength;

    // Output our new sequence value
    DAC::Write(sequence[idx_]);

    // read our latest sample
    history_[idx_] = pin_.Read();
    return history_[idx_];
  }

  void Calibrate() {
    DAC::Write(DAC::max());
    max_ = pin_.ReadAnalog(true);

    DAC::Write(DAC::min());
    min_ = pin_.ReadAnalog(true);

    uint16_t rand = rng() >> 6;  // top 10 bits
    DAC::Write(rand);

    uint16_t read = pin_.ReadAnalog(true);

    assert(read == map(rand, DAC::min(), DAC::max(), min_, max_));
    assert(rand == map(read, min_, max_, DAC::min(), DAC::max()));
  }

  constexpr bool is_connected() const {
    // Compare history to our output sequence
    for (auto i = 0; i < kSequenceLength; ++i) {
      auto idx = (idx_ + i) % kSequenceLength;
      if (history_[idx] != sequence[idx]) {
        return false;
      }
    }
    return true;
  }

  constexpr uint16_t value() const {
    return history_[idx_];
  }

  constexpr uint16_t last() const {
    return history_[idx_ + 1 % kSequenceLength];
  }

  constexpr uint16_t min() const {
    return min_;
  }

  constexpr uint16_t max() const {
    return max_;
  }

  constexpr uint16_t median() const {
    return ((max_ - min_) / 2) + min_;
  }

 private:
  std::array<uint16_t, 8> history_;
  int idx_ = 0;
  Pin pin_;

  uint16_t min_ = ADC::min();
  uint16_t max_ = ADC::max();
};
