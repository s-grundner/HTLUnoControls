/*
@author smon
	3AHEL
*/

#include "Arduino.h"
#include "Controls.h"
#include "math.h"

Controls::Controls()
{

	pin_active = true;
	seg_active = false;
	line_active = false;
	rgb_active = false;

	pinMode(seg, INPUT);
	pinMode(line, INPUT);
	pinMode(rgb, INPUT);

	setPinModeLed(false);
	getMode();

	digitalWrite(led0, HIGH);
}

//Pin Settings

int Controls::getMode()
{
	int testDDRmode = ((DDRB & 0b00011100) >> 0x2);
	switch (testDDRmode)
	{
	case 1:
		pin_active = false;
		seg_active = true;
		line_active = false;
		rgb_active = false;
		break;

	case 2:
		pin_active = false;
		seg_active = false;
		line_active = true;
		rgb_active = false;
		break;

	case 4:
		pin_active = false;
		seg_active = false;
		line_active = false;
		rgb_active = true;
		break;

	default:
		DDRB &= 0b11100011;
		pin_active = true;
		seg_active = false;
		line_active = false;
		rgb_active = false;
		break;
	}
	return testDDRmode;
}

void Controls::setMode(int n)
{
	n = n << 0x2;
	DDRB &= 0b11100011;
	DDRB |= n;
}

void Controls::Mux(int *n)
{
	for (int i = 0; i < sizeof(n) / sizeof(int); i++)
	{
		setMode(n[i]);
		delay(muxTime);
	}
}

//overall LED settings

void Controls::setLed(unsigned long x)
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
		setLED(0b1111111111);
	}
	else
	{
		setLED(0b0000000000);
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
		setLED(out);
	}
	else if (line_active)
	{
		setLED(n);
	}
}

void Controls::setLetter(char c)
{
	switch (c)
	{
	case ('a'):
		setLED(0b0001110111);
		break;

	case ('b'):
		setLED(0b0001111100);
		break;

	case ('c'):
		setLED(0b0000111001);
		break;

	case ('d'):
		setLED(0b0001011110);
		break;

	case ('e'):
		setLED(0b0001111001);
		break;

	case ('f'):
		setLED(0b0001110001);
		break;

	case ('g'):
		setLED(0b0000111101);
		break;

	case ('h'):
		setLED(0b0001110100);
		break;

	case ('i'):
		setLED(0b0000010000);
		break;

	case ('j'):
		setLED(0b0000011110);
		break;

	case ('k'):
		setLED(0b0001110101);
		break;

	case ('l'):
		setLED(0b0000111000);
		break;

	case ('m'):
		NA();
		break;

	case ('n'):
		setLED(0b0001010100);
		break;

	case ('o'):
		setLED(0b0001011100);
		break;

	case ('p'):
		setLED(0b0001110011);
		break;

	case ('q'):
		setLED(0b0001100111);
		break;

	case ('r'):
		setLED(0b0001010000);
		break;

	case ('s'):
		setLED(0b0001101101);
		break;

	case ('t'):
		setLED(0b0001111000);
		break;

	case ('u'):
		setLED(0b0000111110);
		break;

	case ('v'):
		setLED(0b0000011100);
		break;

	case ('w'):
		NA();
		break;

	case ('x'):
		setLED(0b0001110110);
		break;

	case ('y'):
		setLED(0b0001101110);
		break;

	case ('z'):
		setLED(0b0001011011);
		break;

	case (' '):
		setLED(0b0000000000);
		break;
	}
}

// void Controls::Write(char s[])
// {
// 	for (int i = 0; i < sizeof(s) / sizeof(char); i++)
// 	{
// 		setLetter(s[i]);
// 		delay(time);
// 	}
// }

//poti control
double Controls::getPercentageAnalogIn(int n)
{
	float val = analogRead(n);
	float perc = val / 0x3ff;

	return perc;
}

void Controls::showPercentageAnalogIn(int n)
{
	getMode();

	float read = analogRead(n);
	float val = read / 0x3ff;
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
			setLED(0b0000000000);
		}
		else if (perc >= 5 && perc < 15)
		{
			setLED(0b0000000001);
		}
		else if (perc >= 15 && perc < 25)
		{
			setLED(0b0000000011);
		}
		else if (perc >= 25 && perc < 35)
		{
			setLED(0b0000000111);
		}
		else if (perc >= 35 && perc < 45)
		{
			setLED(0b0000001111);
		}
		else if (perc >= 45 && perc < 55)
		{
			setLED(0b0000011111);
		}
		else if (perc >= 55 && perc < 65)
		{
			setLED(0b0000111111);
		}
		else if (perc >= 65 && perc < 75)
		{
			setLED(0b0001111111);
		}
		else if (perc >= 75 && perc < 85)
		{
			setLED(0b0011111111);
		}
		else if (perc >= 85 && perc < 95)
		{
			setLED(0b0111111111);
		}
		else if (perc >= 95)
		{
			setLED(0b1111111111);
		}
	}

	else if (rgb_active)
	{
		Color(val * 0xffffff);
	}
}

void Controls::showPan(int n)
{
	getMode();

	float read = analogRead(n);
	float val = (2 * read / 0x3ff) - 1;
	float perc = val * 100;
	int dec = round(perc / 10);

	if (seg_active)
	{
		setNumber(dec);
	}

	else if (line_active)
	{
		if (perc < -82 )
		{
			setLED(0b0000011111);
		}
		else if (perc >= -82 && perc < -64)
		{
			setLED(0b0000011110);
		}
		else if (perc >= -64 && perc < -46)
		{
			setLED(0b0000011100);
		}
		else if (perc >= -46 && perc < -28)
		{
			setLED(0b0000011000);
		}
		else if (perc >= -28 && perc < -10)
		{
			setLED(0b0000010000);
		}
		else if (perc >= -10 && perc < 10)
		{
			setLED(0b0000000000);
		}
		else if (perc >= 10 && perc < 28)
		{
			setLED(0b0000100000);
		}
		else if (perc >= 28 && perc < 46)
		{
			setLED(0b0001100000);
		}
		else if (perc >= 46 && perc < 64)
		{
			setLED(0b0011100000);
		}
		else if (perc >= 64 && perc < 82)
		{
			setLED(0b0111100000);
		}
		else if (perc >= 82)
		{
			setLED(0b1111100000);
		}
	}

	else if (rgb_active)
	{
		Color(val * 0xffffff);
	}
}
//rgb control

void Controls::Color(long n)
{
	//n: 0-0xffffff
	long r = (n & 0xff0000) >> 0x10;
	long g = (n & 0x00ff00) >> 0x8;
	long b = n & 0x0000ff;

	analogWrite(led5, 0xff - r); //red
	analogWrite(led6, 0xff - g); //green
	analogWrite(led9, 0xff - b); //blue
}

//private Methods

void Controls::setPinModeLed(bool b)
{
	if (b)
	{
		DDRD = 0b00000000;
		DDRB &= 0b11111100;
	}
	else
	{
		DDRD = 0b11111111;
		DDRB &= 0b00000011;
	}
}

void Controls::NA()
{
	setLED(0b0001000000);
	delay(time / 4);
	LEDon(false);
	delay(time / 4);
	setLED(0b0001000000);
	delay(time / 4);
	LEDon(false);
	delay(time / 4);
}