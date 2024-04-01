#pragma once
#include <cstdint>

namespace TWI {
enum class Error {
  ADDRESS_NOT_ACKNOWLEDGED,
  ARBITRATION_LOST,
  TX_INCOMPLETE,
};

inline consteval uint8_t calc_baud(auto freq, auto t_rise) {
  return ((F_CPU / freq) / 2) - (5 + (((F_CPU / 1000000) * t_rise) / 2000));
}

inline void Enable(TWI_t& twi) {
  // Set baud
  twi.MBAUD = calc_baud(400000, 400);  // 2.2kOhm

  // Enable I2C
  twi.MCTRLA = TWI_ENABLE_bm;
  twi.MSTATUS = TWI_BUSSTATE_IDLE_gc;
}

/// @brief RAII I2C Transaction Object
struct Transfer {
  enum Mode { Rx = 1, Tx = 0 };
  std::optional<Error> error = std::nullopt;

  Transfer(TWI_t& twi, uint8_t addr) : twi_(twi), addr_(addr << 1) {
  }
  ~Transfer() {
    Stop();
  }

  void Stop() {
    if (!error) {
      twi_.MCTRLB = twi_.MCTRLB | TWI_MCMD_STOP_gc;  // Issue Stop condition
    }
  }

  void Write(std::span<uint8_t> data) {
    if (!(addr_sent_ && mode_ == Mode::Tx)) {
      SendAddr(Mode::Tx);
    }

    // Otherwise State M1
    for (uint8_t byte : data) {
      twi_.MDATA = byte;

      while (!(twi_.MSTATUS & TWI_WIF_bm)) {
        ;  // Wait for Write Interrupt Flag to be set
      }

      if (twi_.MSTATUS & TWI_RXACK_bm) {  // Received NACK
        Stop();
        error = Error::TX_INCOMPLETE;
        return;
      }
    }
  }

  void WriteOne(uint8_t data) {
    Write({&data, 1});
  }

  void ReadInto(std::span<uint8_t> output) {
    if (!(addr_sent_ && mode_ == Mode::Rx)) {
      SendAddr(Mode::Rx);
    }

    bool first_byte = true;
    for (uint8_t& data : output) {
      if (!first_byte) {
        twi_.MCTRLB = twi_.MCTRLB | TWI_ACKACT_ACK_gc;  // Read further
      }
      first_byte = false;

      while (!(twi_.MSTATUS & TWI_RIF_bm)) {
        ;  // Wait for Read Interrupt Flag to be set
      }
      data = twi_.MDATA;
    }

    twi_.MCTRLB = twi_.MCTRLB | TWI_ACKACT_NACK_gc;  // Done reading data
  }

  uint8_t ReadOne() {
    uint8_t data;
    ReadInto({&data, 1});
    return data;
  }

 private:
  void SendAddr(Mode mode) {
    twi_.MADDR = addr_ | mode;
    mode_ = mode;

    while (!(twi_.MSTATUS & TWI_WIF_bm)) {
      ;  // Wait for Write Interrupt Flag to be set
    }

    if (twi_.MSTATUS & TWI_BUSSTATE_gm != TWI_BUSSTATE_OWNER_gc) {
      // Error, Arbitration lost (State M4)
      error = Error::ARBITRATION_LOST;
      return;
    }

    if (twi_.MSTATUS & TWI_WIF_bm) {
      // State M3 "Address not Acknowledged by Client"
      if (twi_.MSTATUS & TWI_RXACK_bm) {  // Received NACK
        Stop();
        error = Error::ADDRESS_NOT_ACKNOWLEDGED;
      }
    }

    addr_sent_ = true;
  }

  bool addr_sent_ = false;
  Mode mode_;
  uint8_t addr_;
  TWI_t& twi_;
};

inline Transfer StartTransfer(TWI_t& twi, uint8_t addr) {
  return Transfer(twi, addr);
}
};  // namespace TWI
