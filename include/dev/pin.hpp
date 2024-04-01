#pragma once
#include <avr/io.h>

#include <cstdint>

#include "sys/adc.hpp"
#include "util/bit_ops.hpp"
#include "util/misc.hpp"
class Pin {
  PORT_t* port_;
  uint8_t bit_;

 public:
  enum class Mode { INPUT, INPUT_PULLUP, OUTPUT };

  constexpr Pin(PORT_t& p, uint8_t b) : port_{&p}, bit_{b} {};

  void Init(Mode m, bool inverted = false) const {
    if (m == Mode::INPUT || m == Mode::INPUT_PULLUP) {
      port_->DIRCLR = bitmask();
    } else {
      port_->DIRSET = bitmask();
    }

    if (m == Mode::INPUT_PULLUP) {
      port_->PINCTRLSET = port_->PINCTRLSET | PORT_PULLUPEN_bm;
    }

    if (inverted) {
      port_->PINCTRLSET = port_->PINCTRLSET | PORT_INVEN_bm;
    }

    port_->PINCTRLUPD = bitmask();
  }

  constexpr uint8_t bitmask() const {
    return (1 << bit_);
  }

  template <typename T>
  void Write(T value) const {
    port_->OUTSET = value << bit_;
  }

  template <typename T = bool>
  T Read() const {
    return bit::Read<uint8_t>(port_->IN, bit_);
  }

  template <typename T>
  T ReadAnalog(bool inverted = false) const;

  constexpr PORT_t& port() const {
    return *port_;
  }
  constexpr uint8_t bit() const {
    return bit_;
  }

  auto operator<=>(const Pin&) const = default;

 private:
  void SampleADC() const {
    uint8_t analog_input;
    if (port_ == &PORTD) {  // PORTD is default
      analog_input = bit_;
    }
    // else if (port_ == Port::E) {
    //   analog_input = bit_ + 8
    // }
    else if (port_ == &PORTF) {
      analog_input = bit_ + 16;
    }
    ADC::Select(analog_input);
    ADC::Start();

    // Wait for result
    while (!ADC::ResultReady()) {
      ;
    }
  }
};

template <typename T = uint16_t>
T Pin::ReadAnalog(bool inverted) const {
  SampleADC();
  return inverted ? ADC::max() - ADC0.RES : ADC0.RES;
}

template <>
inline uint8_t Pin::ReadAnalog(bool inverted) const {
  SampleADC();
  return inverted ? 0xFF - ADC0.RESH : ADC0.RESH;
}
