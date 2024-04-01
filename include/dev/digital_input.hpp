#pragma once
#include "dev/pin.hpp"
#include "hid/timed_switch.hpp"
#include "util/digital_signal.hpp"

class DigitalInput {
  DigitalSignal signal_;

 public:
  Pin pin;

  DigitalInput(const Pin pin) : pin(pin) {
  }

  void Init(bool inverted = false, bool pullup = false) {
    using enum Pin::Mode;
    pin.Init(pullup ? INPUT_PULLUP : INPUT, inverted);
  }

  bool Read() {
    bool reading = pin.Read();
    signal_.Process(reading);
    return signal_.high();
  }

  bool high() const {
    return signal_.high();
  }
  bool rising() const {
    return signal_.rising();
  }
  bool low() const {
    return signal_.low();
  }
  bool falling() const {
    return signal_.falling();
  }
};

using GateInput = DigitalInput;
using ClockInput = DigitalInput;
using TriggerInput = DigitalInput;
