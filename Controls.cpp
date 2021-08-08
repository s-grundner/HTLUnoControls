/*
@author smon
	3AHEL
*/

#include "Arduino.h"
#include "Controls.h"
#include <math.h>
#include <string.h>

Controls::Controls()
{
	setMode(0b000); //default output on pins

	setPinMode(false); //defines pins 0-9 to output
	getMode();
}

//Pin Settings

void Controls::setPins()
{
	setMode(0b000);
}

void Controls::setHex(bool b)
{
	if (b)
	{
		setMode(getMode() | 0b001);
	}
	else
	{
		setMode(getMode() & 0b110);
	}
}

void Controls::setLine(bool b)
{
	if (b)
	{
		setMode(getMode() | 0b010);
	}
	else
	{
		setMode(getMode() & 0b101);
	}
}

void Controls::setRgb(bool b)
{
	if (b)
	{
		setMode(getMode() | 0b100);
	}
	else
	{
		setMode(getMode() & 0b011);
	}
}

bool Controls::getPinState()
{
	return pin_active;
}

bool Controls::getHexState()
{
	return seg_active;
}

bool Controls::getLineState()
{
	return line_active;
}

bool Controls::getRgbState()
{
	return rgb_active;
}

int Controls::getMode()
{
	int testDDRmode = ((DDRB & 0b00011100) >> 0x2);
	modeAct(testDDRmode);
	return testDDRmode;
}

void Controls::setMode(int n)
{
	n = (n << 0x2) | 0b11;
	DDRB &= 0b11100011;
	DDRB |= n;
	getMode();
}

void Controls::modeAct(int n)
{
	if ((n & 0b001))
	{
		seg_active = true;
	}
	else
	{
		seg_active = false;
	}

	if ((n & 0b010) >> 1)
	{
		line_active = true;
	}
	else
	{
		line_active = false;
	}

	if (n >> 2)
	{
		rgb_active = true;
	}
	else
	{
		rgb_active = false;
	}
}

void Controls::mux(int n[])
{
}

//overall LED settings

void Controls::setOut(unsigned long x)
{
	unsigned long firstEight = x & 0b0011111111;
	unsigned long lastTwo = x >> 0x8;
	PORTB |= 0b00000011;
	PORTB &= ~lastTwo;
	PORTD = ~firstEight;
}

void Controls::ledOn(bool b)
{
	if (b)
	{
		setOut(0b1111111111);
	}
	else
	{
		setOut(0b0000000000);
	}
}

//character display

void Controls::setNumber(int n)
{
	getMode();
	if (seg_active)
	{
		int firstWord = abs(n) & 0xf;
		int out = 0b0000000000;
		if (n < 0)
		{
			out |= 0b0100000000;
		}
		if (n >= 0x10 || n <= -0x10)
		{
			out |= 0b1010000000;
		}
		switch (firstWord)
		{
		case 0x0:
			out |= 0b0000111111;
			break;

		case 0x1:
			out |= 0b0000000110;
			break;

		case 0x2:
			out |= 0b0001011011;
			break;

		case 0x3:
			out |= 0b0001001111;
			break;

		case 0x4:
			out |= 0b0001100110;
			break;

		case 0x5:
			out |= 0b0001101101;
			break;

		case 0x6:
			out |= 0b0001111101;
			break;

		case 0x7:
			out |= 0b0000000111;
			break;

		case 0x8:
			out |= 0b0001111111;
			break;

		case 0x9:
			out |= 0b0001101111;
			break;

		case 0xa:
			out |= 0b0001110111;
			break;

		case 0xb:
			out |= 0b0001111100;
			break;

		case 0xc:
			out |= 0b0000111001;
			break;

		case 0xd:
			out |= 0b0001011110;
			break;

		case 0xe:
			out |= 0b0001111001;
			break;

		case 0xf:
			out |= 0b0001110001;
			break;

		default:
			out = 0b0000111111;
			break;
		}
		setOut(out);
	}
	else if (line_active)
	{
		setOut(n);
	}
}

void Controls::setLetter(char c)
{
	switch (c)
	{
	case ('a'):
		setOut(0b0001110111);
		break;

	case ('b'):
		setOut(0b0001111100);
		break;

	case ('c'):
		setOut(0b0000111001);
		break;

	case ('d'):
		setOut(0b0001011110);
		break;

	case ('e'):
		setOut(0b0001111001);
		break;

	case ('f'):
		setOut(0b0001110001);
		break;

	case ('g'):
		setOut(0b0000111101);
		break;

	case ('h'):
		setOut(0b0001110100);
		break;

	case ('i'):
		setOut(0b0000010000);
		break;

	case ('j'):
		setOut(0b0000011110);
		break;

	case ('k'):
		setOut(0b0001110101);
		break;

	case ('l'):
		setOut(0b0000111000);
		break;

	case ('m'):
		na();
		break;

	case ('n'):
		setOut(0b0001010100);
		break;

	case ('o'):
		setOut(0b0001011100);
		break;

	case ('p'):
		setOut(0b0001110011);
		break;

	case ('q'):
		setOut(0b0001100111);
		break;

	case ('r'):
		setOut(0b0001010000);
		break;

	case ('s'):
		setOut(0b0001101101);
		break;

	case ('t'):
		setOut(0b0001111000);
		break;

	case ('u'):
		setOut(0b0000111110);
		break;

	case ('v'):
		setOut(0b0000011100);
		break;

	case ('w'):
		na();
		break;

	case ('x'):
		setOut(0b0001110110);
		break;

	case ('y'):
		setOut(0b0001101110);
		break;

	case ('z'):
		setOut(0b0001011011);
		break;

	case (' '):
		setOut(0b0000000000);
		break;
	}
}

void Controls::write(char *, int len)
{
	for (int i = 0; i < len; i++)
	{
		setLetter(s[i]);
		delay(time);
	}
}

//poti control
float Controls::getPercentageAnalogIn(int n)
{
	float val = analogRead(n);
	float perc = val / 1024;

	return perc;
}

void Controls::showPercentageAnalogIn(int n)
{
	getMode();

	float read = analogRead(n);
	float val = read / 1024;
	float perc = val * 100;
	int dec = round(perc / 10);

	if (seg_active)
	{
		setNumber(dec);
	}

	else if (line_active)
	{
		if (perc < 5)
		{
			setOut(0b0000000000);
		}
		else if (perc >= 5 && perc < 15)
		{
			setOut(0b0000000001);
		}
		else if (perc >= 15 && perc < 25)
		{
			setOut(0b0000000011);
		}
		else if (perc >= 25 && perc < 35)
		{
			setOut(0b0000000111);
		}
		else if (perc >= 35 && perc < 45)
		{
			setOut(0b0000001111);
		}
		else if (perc >= 45 && perc < 55)
		{
			setOut(0b0000011111);
		}
		else if (perc >= 55 && perc < 65)
		{
			setOut(0b0000111111);
		}
		else if (perc >= 65 && perc < 75)
		{
			setOut(0b0001111111);
		}
		else if (perc >= 75 && perc < 85)
		{
			setOut(0b0011111111);
		}
		else if (perc >= 85 && perc < 95)
		{
			setOut(0b0111111111);
		}
		else if (perc >= 95)
		{
			setOut(0b1111111111);
		}
	}

	else if (rgb_active)
	{
		color(val * 0xffffff);
	}
}

void Controls::showPan(int n)
{
	getMode();

	float read = analogRead(n);
	float val = (2 * read / 1024) - 1;
	float perc = val * 100;
	int dec = round(perc / 10);

	if (seg_active)
	{
		setNumber(dec);
	}

	else if (line_active)
	{
		if (perc < -82)
		{
			setOut(0b0000011111);
		}
		else if (perc >= -82 && perc < -64)
		{
			setOut(0b0000011110);
		}
		else if (perc >= -64 && perc < -46)
		{
			setOut(0b0000011100);
		}
		else if (perc >= -46 && perc < -28)
		{
			setOut(0b0000011000);
		}
		else if (perc >= -28 && perc < -10)
		{
			setOut(0b0000010000);
		}
		else if (perc >= -10 && perc < 10)
		{
			setOut(0b0000000000);
		}
		else if (perc >= 10 && perc < 28)
		{
			setOut(0b0000100000);
		}
		else if (perc >= 28 && perc < 46)
		{
			setOut(0b0001100000);
		}
		else if (perc >= 46 && perc < 64)
		{
			setOut(0b0011100000);
		}
		else if (perc >= 64 && perc < 82)
		{
			setOut(0b0111100000);
		}
		else if (perc >= 82)
		{
			setOut(0b1111100000);
		}
	}

	else if (rgb_active)
	{
		color(val * 0xffffff);
	}
}
//rgb control

void Controls::color(long n)
{
	//n: 0-0xffffff
	long r = (n & 0xff0000) >> 0x10;
	long g = (n & 0x00ff00) >> 0x8;
	long b = n & 0x0000ff;

	analogWrite(led5, 0xff - r); //red
	analogWrite(led6, 0xff - g); //green
	analogWrite(led9, 0xff - b); //blue
}

void Controls::color(int r, int g, int b)
{
	analogWrite(led5, 0xff - r); //red
	analogWrite(led6, 0xff - g); //green
	analogWrite(led9, 0xff - b); //blue
}
// ------------------------------
// private Methods

void Controls::setPinMode(bool b)
{
	if (b) //sets all pins to input
	{
		DDRD = 0b00000000;
		DDRB &= 0b11111100;
	}
	else //sets all leds to output
	{
		DDRD = 0b11111111;
		DDRB &= 0b00000011;
	}
}

void Controls::na()
{
	setOut(0b0001000000);
	delay(time / 4);
	ledOn(false);
	delay(time / 4);
	setOut(0b0001000000);
	delay(time / 4);
	ledOn(false);
	delay(time / 4);
}
