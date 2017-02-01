Samsung 16LF01 series VFD Library for Arduino
============================
[![Build Status](https://travis-ci.org/DnaX/Samsung_16LF01_VFD.svg?branch=master)](https://travis-ci.org/DnaX/Samsung_16LF01_VFD)

_Written by Daniele Napolitano, distributed under GPL._

Samsung_16LF01_VFD is an Arduino library designed for displaying characters on Samsung 16LF01 series 16-segments VFD with synchronous serial protocol. The API used tries to be compatible with the [LiquidCrystal](http://arduino.cc/en/Reference/LiquidCrystal) library.

Samsung_16LF01_VFD fully tested with the following displays:

 * Samsung 16LF01UA3
    

Usage
-----

You need to include library header at the beginning of the sketch.

```C++
#include <Samsung_16LF01_VFD.h>
```

The library class inherits the Print class of Arduino, so that you can display texts (not all chars supported) on VFD with standard Arduino functions like this:

```C++
vfd.print("Hello, World!";)
vfd.print(foo, DEC);
vfd.print(bar, HEX);
vfd.print(1.23)         // gives "1.23" 
vfd.print(1.23456, 2);  // gives "1.23" 
vfd.println("hello");   // prints "hello" and return to position 0
```

Besides, it provides unified APIs for initializing and controlling the VFD, as well as some convenient operations.

```C++
void begin(uint8_t digits_count, uint8_t brightness); /* initializing */
void clear(); /* clear screen */
void home(); /* set cursor at first digit */
void setCursor(uint8_t pos); /* set current cursor (from 0) */
void setBrightness(uint8_t amount); /* set current display brightness */
```

Example
-------

```C++
/********************
  Pin config:
  
  SCLK = pin 7
  RST  = pin 6
  DATA = pin 5
*********************/

#include <Samsung_16LF01_VFD.h>

Samsung_16LF01_VFD vfd(7, 5, 6);

void setup() {
  vfd.begin(16, 15);
  vfd.print("Hello World!");
  delay(3000);
}

void loop() {
  vfd.print(millis() / 1000);
  vfd.println(" s");
  delay(1000);
}
```

