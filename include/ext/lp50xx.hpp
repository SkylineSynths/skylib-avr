#pragma once
#include <cassert>
#include <cstdint>
#include <optional>
#include <span>

#include "sys/twi.hpp"
#include "util/color.hpp"

class LP50xx {
  struct Register {
    enum : uint8_t {
      DEVICE_CONFIG0 = 0x00,
      DEVICE_CONFIG1 = 0x01,
      LED_CONFIG0 = 0x02,
      BANK_BRIGHTNESS = 0x03,
      BANK_COLOR = 0x04,
      LED_BRIGHTNESS = 0x07,
      OUT_COLOR = 0x0B,
      RESET = 0x27,
    };
  };

 public:
  LP50xx(TWI_t& twi, uint8_t addr) : twi_(twi), addr_(addr){};

  void Write(uint8_t reg, std::span<uint8_t> data) {
    auto transfer = TWI::StartTransfer(twi_, addr_);
    transfer.WriteOne(reg);
    transfer.Write(data);
  }

  void Write(uint8_t reg, uint8_t data) {
    std::array reg_data{reg, data};
    TWI::StartTransfer(twi_, addr_).Write(reg_data);
  }

  void ReadInto(uint8_t reg, std::span<uint8_t> out) {
    auto transfer = TWI::StartTransfer(twi_, addr_);
    transfer.WriteOne(reg);
    // transfer.ReadInto(out);
  }

  template <size_t num>
  std::array<uint8_t, num> Read(uint8_t reg) {
    std::array<uint8_t, num> output;
    ReadInto(reg, output);
    return output;
  }

  uint8_t Read(uint8_t reg) {
    auto transfer = TWI::StartTransfer(twi_, addr_);
    transfer.WriteOne(reg);
    return transfer.ReadOne();
  }

  void Enable() {
    Write(Register::DEVICE_CONFIG0, 1 << 6);
  }

  void SetBrightness(uint8_t led, uint8_t value) {
    assert(led < 8);
    uint8_t reg_addr = Register::LED_BRIGHTNESS + led;
    Write(reg_addr, value);
  }

  void SetBrightnessAll(std::array<uint8_t, 8> brightness) {
    Write(Register::LED_BRIGHTNESS, brightness);
  }

  uint8_t GetBrightness(uint8_t led) {
    assert(led < 8);
    uint8_t reg_addr = Register::LED_BRIGHTNESS + led;
    return Read(reg_addr);
  }

  void SetColor(uint8_t led, RGB c) {
    assert(led < 8);
    Write(Register::OUT_COLOR + led, c.as_span());
  }

  void SetColorAll(std::array<RGB, 8> c) {
    Write(Register::OUT_COLOR, std::span<uint8_t>{&c[0].r, 8 * 3});
  }

  void GetColor(uint8_t led, RGB c) {
    assert(led < 8);
    Write(Register::OUT_COLOR + led, c.as_span());
  }

  void Clear() {
    auto transfer = TWI::StartTransfer(twi_, addr_);
    transfer.WriteOne(Register::OUT_COLOR);
    for (uint8_t i = 0; i < 8; i++) {
      transfer.WriteOne(0x00);
    }
  }

  std::array<RGB, 8> GetColors() {
    std::array<RGB, 8> colors;
    ReadInto(Register::OUT_COLOR, {&colors[0].r, 8 * 3});
    return colors;
  }

 private:
  TWI_t& twi_;
  uint8_t addr_;
};
