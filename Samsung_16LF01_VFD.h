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
 
#ifndef Samsung_16LF01_VFD_h
#define Samsung_16LF01_VFD_h

#include <inttypes.h>
#include "Print.h"

#define VFD_CMD_BUFFER_POINTER B10100000
#define VFD_CMD_DIGIT_COUNTER B11000000
#define VFD_CMD_MASK B00001111
#define VFD_CMD_BRIGHTNESS B11100000
#define VFD_CMD_BRIGHTNESS_MASK B00011111


class Samsung_16LF01_VFD : public Print {
public:
  Samsung_16LF01_VFD(uint8_t _SCLK, uint8_t _DATA, uint8_t _RST);

  void begin(uint8_t digits_count, uint8_t brightness);
  
  void clear();
  void home();

  void setCursor(uint8_t pos);
  void setBrightness(uint8_t amount);

  virtual size_t write(uint8_t);

  using Print::write;

private:
  void sendCommand(uint8_t data);
  void setDigitsCount(uint8_t digits);
  void reset();

  uint8_t _sclk_pin;
  uint8_t _data_pin;
  uint8_t _rst_pin;
  
  uint8_t _digits_count;
};

#endif
