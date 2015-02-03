Samsung 16LF01 series VFD Library for Arduino
============================

_Written by Daniele Napolitano, distributed under GPL._

Samsung_16LF01_VFD is an Arduino library designed for displaying characters on Samsung 16LF01 series 16 segment VFD with synchronous serial protocol. The API used tries to be compatible with the [LiquidCrystal](http://arduino.cc/en/Reference/LiquidCrystal) library.

Samsung_16LF01_VFD is tested with the following displays:

 * Samsung 16LF01UA3
    

Usage
-----

You need to include library header at the beginning of the sketch.

```C++
#include <Samsung_16LF01_VFD.h>
```

The library class inherits the Print class of Arduino, so that you can display texts (not all chars supported) on VFD with standard Arduino functions like this:

```C++
lcd.print("Hello, World!";)
lcd.print(foo, DEC);
lcd.print(bar, HEX);
lcd.print(1.23)         // gives "1.23" 
lcd.print(1.23456, 2);  // gives "1.23" 
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
  vfd.setCursor(0);
  vfd.print(millis() / 1000);
}
```
