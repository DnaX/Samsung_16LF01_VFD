/*
 * Samsung_16LF01_VFD - Library for Samsung 16LF01 series 16 segments
 * vacuum fluorescent displays (VFD).
 *
 * Full tested with the Samsung 16LF01UA3 display.
 *
 * This library tries to be compatible with the LiquidCrystal library.
 *
 * Copyright (c) 2015 Daniele Napolitano <dnax88@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "Samsung_16LF01_VFD.h"

/**
 * When the display powers up, it is configured as follows:
 * Position: 1
 * Digits count: 16
 * Brightness: 0
 **/

Samsung_16LF01_VFD::Samsung_16LF01_VFD(uint8_t _SCLK, uint8_t _DATA, uint8_t _RST) {
  // Set internals
  _sclk_pin = _SCLK;
  _data_pin = _DATA;
  _rst_pin = _RST;
  
  // Configure pins
  pinMode(_sclk_pin, OUTPUT);
  pinMode(_data_pin, OUTPUT);
  pinMode(_rst_pin, OUTPUT);
}

// Init the display with 16 digits and mid level brightness
void Samsung_16LF01_VFD::begin(uint8_t digits_count = 16, uint8_t brightness = 15) {
  // First reset the display
  reset();
  // Then set the digits count (default: 16)
  setDigitsCount(digits_count);
  // So, clear the digit buffer
  clear();
  // Then light up the display (with buffer clear, no random RAM data)
  setBrightness(brightness);
}

// Blank the display by setting up to 16 spaces
void Samsung_16LF01_VFD::clear() {
  setCursor(0);
  for (int i=0; i<_digits_count; i++) {
    write(' ');
  }
}

// Return to position 1
void Samsung_16LF01_VFD::home() { 
  setCursor(0);
}


// Set buffer poiner position.
void Samsung_16LF01_VFD::setCursor(uint8_t pos) {
  if (pos > 15) {
    pos = 15;
  }
  
  // First digit value is B1111, from second start from 0
  if (pos == 0) {
    pos = B1111;
  }
  else {
    pos--;
  }
  
  pos &= VFD_CMD_MASK;
  sendCommand(VFD_CMD_BUFFER_POINTER | pos);
}

// Set display brightness, from 0 to 31.
void Samsung_16LF01_VFD::setBrightness(uint8_t amount) {
  if (amount > 31) {
    amount = 31;
  }
  amount &= VFD_CMD_BRIGHTNESS_MASK;
  sendCommand(VFD_CMD_BRIGHTNESS | amount);
}

// Write a char on the display
inline size_t Samsung_16LF01_VFD::write(uint8_t _char) {
  // First set of charmap (letters ad some symbols)
  if (_char >= 64 && _char <= 95) {
    sendCommand(_char - 64);
  }
  // Second set of charmap (numbers and some symbols)
  else if (_char >= 32 && _char <= 63) {
    sendCommand(_char);
  }
  // Lower case letters
  else if (_char >= 97 && _char <= 122) {
    sendCommand(_char - 96);
  }
  // If we get a return carrier, return to position 0.
  if (_char == '\r' || _char == '\n') {
    setCursor(0);
  }
  return 1;
}

// Reset the display.
void Samsung_16LF01_VFD::reset() {
  // Spec needs RST signal for above 1ms
  digitalWrite(_rst_pin, LOW);
  delay(2);
  digitalWrite(_rst_pin, HIGH); 
  delay(2); 
}

// Send serial data to the display
void Samsung_16LF01_VFD::sendCommand(uint8_t data) {
  for (int i=7; i>=0; i--) {
    digitalWrite(_data_pin, bitRead(data, i));
        
    digitalWrite(_sclk_pin, HIGH);
    delayMicroseconds(2);
    digitalWrite(_sclk_pin, LOW); 
    delayMicroseconds(2);
    digitalWrite(_sclk_pin, HIGH);
    
    // Internal processing time (40us)
    delayMicroseconds(50);
  }
}

// Set number of digits to control.
void Samsung_16LF01_VFD::setDigitsCount(uint8_t digits = 16) {
  if (digits > 16) {
    digits = 16;
  }
  
  _digits_count = digits;
  
  digits &= VFD_CMD_MASK;
  sendCommand(VFD_CMD_DIGIT_COUNTER | digits);
}
