/*
@author smon
	3AHEL
*/

#include "Arduino.h"
#include "Controls.h"
#include "math.h"

Controls::Controls() {

	pin_active = true;
	seg_active = false;
	line_active = false;
	rgb_active = false;

	pinMode(seg, INPUT);
	pinMode(line, INPUT);
	pinMode(rgb, INPUT);

	setPinModeLed(false);

	digitalWrite(led0, HIGH);

}

//Pin Settings

void Controls::setMode(int n) {
	switch (n) {
	case(0):
		DDRB &= 0b11100011;
		
		pin_active = true;
		seg_active = false;
		line_active = false;
		rgb_active = false;

		setPinModeLed(false);
		
		break;
	
	case(1):
		DDRB &= 0b11100011;
		DDRB |= 0b00000100;

		pin_active = false;
		seg_active = true;
		line_active = false;
		rgb_active = false;

		setPinModeLed(false);
		
		break;


	case(2):
		DDRB &= 0b11100011;
		DDRB |= 0b00001000;

		pin_active = false;
		seg_active = false;
		line_active = true;
		rgb_active = false;
		
		setPinModeLed(false);

		break;

	case(3):
		DDRB &= 0b11100011;
		DDRB |= 0b00010000;

		pin_active = false;
		seg_active = false;
		line_active = false;
		rgb_active = true;

		setPinModeLed(false);
		
		break;
	
	default:
		DDRB &= 0b11100011;
		
		pin_active = true;
		seg_active = false;
		line_active = false;
		rgb_active = false;

		setPinModeLed(false);
		
		break;
	}
}

void Controls::Mux(int * n) {
	for(int i = 0; i < sizeof(n)/sizeof(int); i++) {
		setMode(n[i]);
		delay(muxTime);
	}
}

//overall LED settings

void Controls::setLED(unsigned long x) {
	unsigned long firstEight = x & 0b0011111111;
	unsigned long lastTwo = x >> 0x8;
	PORTB |= 0b00000011;
	PORTB &= ~lastTwo;
	PORTD = ~firstEight;
}

void Controls::LEDon(bool b)
{
	if (b) {
		digitalWrite(led0, LOW);
		digitalWrite(led1, LOW);
		digitalWrite(led2, LOW);
		digitalWrite(led3, LOW);
		digitalWrite(led4, LOW);
		digitalWrite(led5, LOW);
		digitalWrite(led6, LOW);
		digitalWrite(led7, LOW);
		digitalWrite(led8, LOW);
		digitalWrite(led9, LOW);
	}
	else {
		digitalWrite(led0, HIGH);
		digitalWrite(led1, HIGH);
		digitalWrite(led2, HIGH);
		digitalWrite(led3, HIGH);
		digitalWrite(led4, HIGH);
		digitalWrite(led5, HIGH);
		digitalWrite(led6, HIGH);
		digitalWrite(led7, HIGH);
		digitalWrite(led8, HIGH);
		digitalWrite(led9, HIGH);
	}
	
}

//Character display

void Controls::setNumber(int n)
{

}

void Controls::setLetter(char c)
{
	switch (c) {
	case('a'):
		setLED(0b0001110111);
		break;

	case('b'):
		setLED(0b0001111100);
		break;

	case('c'):
		setLED(0b0000111001);
		break;

	case('d'):
		setLED(0b0001011110);
		break;

	case('e'):
		setLED(0b0001111001);
		break;

	case('f'):
		setLED(0b0001110001);
		break;

	case('g'):
		setLED(0b0000111101);
		break;

	case('h'):
		setLED(0b0001110100);
		break;

	case('i'):
		setLED(0b0000010000);
		break;

	case('j'):
		setLED(0b0000011110);
		break;

	case('k'):
		setLED(0b0001110101);
		break;

	case('l'):
		setLED(0b0000111000);
		break;

	case('m'):
		NA();
		break;

	case('n'):
		setLED(0b0001010100);
		break;

	case('o'):
		setLED(0b0001011100);
		break;

	case('p'):
		setLED(0b0001110011);
		break;

	case('q'):
		setLED(0b0001100111);
		break;

	case('r'):
		setLED(0b0001010000);
		break;

	case('s'):
		setLED(0b0001101101);
		break;

	case('t'):
		setLED(0b0001111000);
		break;

	case('u'):
		setLED(0b0000111110);
		break;

	case('v'):
		setLED(0b0000011100);
		break;

	case('w'):
		NA();
		break;

	case('x'):
		setLED(0b0001110110);
		break;

	case('y'):
		setLED(0b0001101110);
		break;

	case('z'):
		setLED(0b0001011011);
		break;

	case(' '):
		setLED(0b0000000000);
		break;
	}
}

void Controls::Write(char s[], int length)
{
	for (int i = 0; i < length; i++) {
		setLetter(s[i]);
		delay(time);
	}
}

//poti control

void Controls::showPercentage(int n)
{
	double val = analogRead(n);
	double perc = (100 * val) / 1023;
	int dec = pot_correction + perc / 10;

	if (seg_active)
	{
		setNumber(dec);
	}

	else if (line_active) {
		if (perc < 5) {
			setLED(0b0000000000);
		}
		else if (perc >= 5 && perc < 15) {
			setLED(0b0000000001);
		}
		else if (perc >= 15 && perc < 25) {
			setLED(0b0000000011);
		}
		else if (perc >= 25 && perc < 35) {
			setLED(0b0000000111);
		}
		else if (perc >= 35 && perc < 45) {
			setLED(0b0000001111);
		}
		else if (perc >= 45 && perc < 55) {
			setLED(0b0000011111);
		}
		else if (perc >= 55 && perc < 65) {
			setLED(0b0000111111);
		}
		else if (perc >= 65 && perc < 75) {
			setLED(0b0001111111);
		}
		else if (perc >= 75 && perc < 85) {
			setLED(0b0011111111);
		}
		else if (perc >= 85 && perc < 95) {
			setLED(0b0111111111);
		}
		else if (perc >= 95) {
			setLED(0b1111111111);
		}
	}

	else if (rgb_active) {
		Color(val*0x3ff);
	}

}

double Controls::getPercentage(int n)
{
	double val = analogRead(n);
	double perc = (100.0 * val) / 1023.0;

	return perc;
}

//rgb control

void Controls::Color(long n)
{
	//n: 0-0xffffff
	long r = (n & 0xff0000) >> 0x10;
	long g = (n & 0x00ff00) >> 0x8;
	long b = n & 0x0000ff;

	analogWrite(led5, 0xff-r);	//red
	analogWrite(led6, 0xff-g);	//green
	analogWrite(led9, 0xff-b);	//blue
}

//private Methods

void Controls::setPinModeLed(bool b)
{
	if(b) {
		pinMode(led0, INPUT);
		pinMode(led1, INPUT);
		pinMode(led2, INPUT);
		pinMode(led3, INPUT);
		pinMode(led4, INPUT);
		pinMode(led5, INPUT);
		pinMode(led6, INPUT);
		pinMode(led7, INPUT);
		pinMode(led8, INPUT);
		pinMode(led9, INPUT);
	} else {
		pinMode(led0, OUTPUT);
		pinMode(led1, OUTPUT);
		pinMode(led2, OUTPUT);
		pinMode(led3, OUTPUT);
		pinMode(led4, OUTPUT);
		pinMode(led5, OUTPUT);
		pinMode(led6, OUTPUT);
		pinMode(led7, OUTPUT);
		pinMode(led8, OUTPUT);
		pinMode(led9, OUTPUT);
	}
}

void Controls::NA()
{
	setLED(0001000000);
	delay(time / 4);
	LEDon(false);
	delay(time / 4);
	setLED(0001000000);
	delay(time / 4);
	LEDon(false);
	delay(time / 4);
}