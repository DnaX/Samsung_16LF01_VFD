/********************
  Pin config:
  
  SCLK = pin 7
  RST  = pin 6
  DATA = pin 5
*********************/

#include <Samsung_16LF01_VFD.h>

Samsung_16LF01_VFD vfd(7, 5, 6);

char message[] = "A cat with a Geiger counter and a bit of poison in a sealed box     ";
char digits[17] = "                ";
int i;
int firstDigit = 0;
int lastDigit = strlen(message) - 1;

void setup()
{
	/*Initialize the display (number of digits to use, brightness)*/
	vfd.begin (16,3);
	
	/*Test the screen with a welcome static message*/
	vfd.print("hello!!");
	delay(999);
	vfd.clear();

	/*Go to the first digit display*/
	vfd.setCursor(0);
}

void loop()
{
	for(i = 0; i < 15; i++)
		digits[i] = digits[i + 1];
	digits[15] = message[firstDigit];

	if (firstDigit == lastDigit)
		firstDigit = 0;
	else
		firstDigit = firstDigit + 1;

	for (i = 0; i < 16; i++) {
		vfd.print(digits[i]);

		/*Workaround, "points" and "commas" are in the same digit*/
		if (digits[i] == ',' || digits[i] == '.')
			vfd.print(" ");
	}

	delay(255);
}
