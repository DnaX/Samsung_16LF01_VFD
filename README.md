Samsung 16LF01 series VFD Library for Arduino [![Build Status](https://github.com/DnaX/Samsung_16LF01_VFD/workflows/Arduino%20Library%20CI/badge.svg)](https://github.com/DnaX/Samsung_16LF01_VFD/actions)
============================

_Written by Daniele Napolitano, distributed under GPL._

**Samsung_16LF01_VFD is an Arduino library designed to drive characters 14/16-segments vacuum fluorescent display (VFD)** with synchronous serial protocol (_like_ SPI, but with different timing). The library, initially written to support the Samsung 16LF01UA3 display module, it's compatible with all displays using the **Rockwell 10937**, **OKI MSC1937-01** and **Micrel MIC10937** controllers.

The API used tries to be compatible with the [LiquidCrystal](http://arduino.cc/en/Reference/LiquidCrystal) library.

Compatible displays
-----

The library Samsung_16LF01_VFD is fully tested with the following displays:

 * Samsung 16LF01UA3: 16-segments, 1x16 characters, uses OKI MSC1937-01
    
![display_photo](http://www.vfdsamsung.com/pics-vfd/16LF01UA3-4.jpg)

Its known the existence of these Samsung VFD displays with the same Sync Serial protocol ([see here](https://www.giant-supplier.com/VFDSAMSUNG/vfd-graphic1.html)):

 * 16LF01UA4: 16-segments, 1x16 character, uses OKI MSC1937-0
 * 9MS09SS1: 14-segments, 1x9 characters, uses ML9209-xx / Nuvoton W78E052DPG (see see [#3](https://github.com/DnaX/Samsung_16LF01_VFD/issues/3))
 * VFM161LSA1: 1x16 characters, uses OKI MSC1937-01) (tested, [img](https://i.imgur.com/4vu5bco.jpg), see [#2](https://github.com/DnaX/Samsung_16LF01_VFD/issues/2))
 * 

Perhaps other display from Samsung or other manufacturers share the same protocol, let me know :)

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
void setBrightness(uint8_t amount); /* set current display brightness (values allowed from 0 to 31) */
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
  // Initialize the display with 16 characters and medium brightness (values allowed from 0 to 31)
  vfd.begin(16, 15);
  vfd.print("Hello World!");
  delay(3000);
}

void loop() {
  // Prints the seconds elapsed since the initialization of the device
  vfd.print(millis() / 1000);
  vfd.println(" s");
  delay(1000);
}
```
