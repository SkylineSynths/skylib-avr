#pragma once
#include <cstdint>
#include <numeric>

/** xoroshiro32++. Very fast, not-cryptographic random number generator. */
class Xoroshiro32PlusPlus {
 public:
  using result_type = uint16_t;

  void Seed(uint16_t s0, uint16_t s1) {
    this->s0 = s0;
    this->s1 = s1;
    // A bad seed will give a bad first result, so shift the state
    operator()();
  }

  bool is_seeded() {
    return s0 || s1;
  }

  result_type operator()() {
    uint16_t result = rotl(s0 + s1, 7) + s0;

    s1 ^= s0;
    s0 = rotl(s0, 13) ^ s1 ^ (s1 << 3);
    s1 = rotl(s1, 9);

    return result;
  }
  constexpr result_type min() const {
    return std::numeric_limits<result_type>::min();
  }
  constexpr result_type max() const {
    return std::numeric_limits<result_type>::max();
  }

 private:
  [[gnu::always_inline]] static constexpr uint16_t rotl(uint16_t x, int k) {
    return (x << k) | (x >> (16 - k));
  }
  uint16_t s0, s1;
};

extern Xoroshiro32PlusPlus rng;
