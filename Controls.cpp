#include "Arduino.h"
#include "Controls.h"
#include "math.h"
#include "Bit.h"

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
		pinMode(seg, INPUT);
		pinMode(line, INPUT);
		pinMode(rgb, INPUT);

		pin_active = true;
		seg_active = false;
		line_active = false;
		rgb_active = false;

		setPinModeLed(false);
		
		break;
	
	case(1):
		pinMode(seg, OUTPUT);
		pinMode(line, INPUT);
		pinMode(rgb, INPUT);

		pin_active = false;
		seg_active = true;
		line_active = false;
		rgb_active = false;

		setPinModeLed(false);
		
		break;


	case(2):
		pinMode(seg, INPUT);
		pinMode(line, OUTPUT);
		pinMode(rgb, INPUT);

		pin_active = false;
		seg_active = false;
		line_active = true;
		rgb_active = false;
		
		setPinModeLed(false);

		break;

	case(3):
		pinMode(seg, INPUT);
		pinMode(line, INPUT);
		pinMode(rgb, OUTPUT);

		pin_active = false;
		seg_active = false;
		line_active = false;
		rgb_active = true;

		setPinModeLed(false);
		
		break;
	
	default:
		break;
	}
}

void Controls::Mux(int n[]) {
	for(int i = 0; i < sizeof(n)/sizeof(int); i++) {
		setMode(n[i]);
		delay(muxTime);
	}
}

//overall LED settings

void Controls::setLED(unsigned long x) {
	
}

void Controls::LEDon(bool b) {
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

void Controls::setByte(int n) {
	n & 0x1 ? digitalWrite(led0, LOW) : digitalWrite(led0, HIGH);
	n & 0x2 ? digitalWrite(led1, LOW) : digitalWrite(led1, HIGH);
	n & 0x4 ? digitalWrite(led2, LOW) : digitalWrite(led2, HIGH);
	n & 0x8 ? digitalWrite(led3, LOW) : digitalWrite(led3, HIGH);
	n & 0x10 ? digitalWrite(led4, LOW) : digitalWrite(led4, HIGH);
	n & 0x20 ? digitalWrite(led5, LOW) : digitalWrite(led5, HIGH);
	n & 0x40 ? digitalWrite(led6, LOW) : digitalWrite(led6, HIGH);
	n & 0x80 ? digitalWrite(led7, LOW) : digitalWrite(led7, HIGH);
	n & 0x100 ? digitalWrite(led8, LOW) : digitalWrite(led8, HIGH);
	n & 0x200 ? digitalWrite(led9, LOW) : digitalWrite(led9, HIGH);
}

void Controls::setNumber(int n) {

	// if (n < -19 || n > 19) {
	// 	NA();
	// }
	// else {
	// 	if (n < 0) {
	// 		Minus(true);
	// 		n = abs(n);
	// 	}
	// 	else {
	// 		Minus(false);
	// 	}

	// 	if (n >= 10) {
	// 		Decade(true);
	// 		n = n - 10;
	// 	}
	// 	else {
	// 		Decade(false);
	// 	}

	// 	switch (n) {
	// 	case(0):
	// 		defLED("1111110");
	// 		break;

	// 	case(1):
	// 		defLED("0110000");
	// 		break;

	// 	case(2):
	// 		defLED("1101101");
	// 		break;

	// 	case(3):
	// 		defLED("1111001");
	// 		break;

	// 	case(4):
	// 		defLED("0110011");
	// 		break;

	// 	case(5):
	// 		defLED("1011011");
	// 		break;

	// 	case(6):
	// 		defLED("1011111");
	// 		break;

	// 	case(7):
	// 		defLED("1110000");
	// 		break;

	// 	case(8):
	// 		defLED("1111111");
	// 		break;

	// 	case(9):
	// 		defLED("1111011");
	// 		break;
	// 	}

	// }
}

void Controls::setLetter(char c) {
	switch (c) {
	case('a'):
		setLED(0b1110111000);
		break;

	case('b'):
		setLED(0b0011111000);
		break;

	case('c'):
		setLED(0b1001110000);
		break;

	case('d'):
		setLED(0b0111101000);
		break;

	case('e'):
		setLED(0b1001111000);
		break;

	case('f'):
		setLED(0b1000111000);
		break;

	case('g'):
		setLED(0b1011110000);
		break;

	case('h'):
		setLED(0b0010111000);
		break;

	case('i'):
		setLED(0b0000100000);
		break;

	case('j'):
		setLED(0b0111100000);
		break;

	case('k'):
		NA();
		break;

	case('l'):
		setLED(0b0001110000);
		break;

	case('m'):
		NA();
		break;

	case('n'):
		setLED(0b0010101000);
		break;

	case('o'):
		setLED(0b0011101000);
		break;

	case('p'):
		setLED(0b1100111000);
		break;

	case('q'):
		setLED(0b1110011000);
		break;

	case('r'):
		setLED(0b0000101000);
		break;

	case('s'):
		setLED(0b1011011000);
		break;

	case('t'):
		setLED(0b0001111000);
		break;

	case('u'):
		setLED(0b0111110000);
		break;

	case('v'):
		setLED(0b0011100000);
		break;

	case('w'):
		NA();
		break;

	case('x'):
		setLED(0b0110111000);
		break;

	case('y'):
		setLED(0b0111011000);
		break;

	case('z'):
		setLED(0b1101101000);
		break;

	case(' '):
		setLED(0b0000000000);
		break;
	}
}

void Controls::Write(char s[], int length) {
	for (int i = 0; i < length; i++) {
		setLetter(s[i]);
		delay(time);
	}
}

//poti control

void Controls::showPercentage(int n) {
	double val = analogRead(n);
	double perc = (100 * val) / 1023;
	int dec = pot_correction + perc / 10;

	if (seg_active) {
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
			setLED(0b0000111111);
		}
		else if (perc >= 55 && perc < 65) {
			setLED(0b0001111111);
		}
		else if (perc >= 65 && perc < 75) {
			setLED(0b0011111111);
		}
		else if (perc >= 75 && perc < 85) {
			setLED(0b0111111111);
		}
		else if (perc >= 85 && perc < 95) {
			setLED(0b1111111111);
		}
		else if (perc >= 95) {
			setLED(0b1111111111);
		}
	}

	else if (rgb_active) {
		Color(val/128);
	}

}

double Controls::getPercentage(int n) {
	double val = analogRead(n);
	double perc = (100.0 * val) / 1023.0;

	return perc;
}

//rgb control

void Controls::Color(int n) {
	//n: 0-8
	n & 0x1 ? digitalWrite(led5, HIGH) : digitalWrite(led5, LOW);
	n & 0x2 ? digitalWrite(led6, HIGH) : digitalWrite(led6, LOW);
	n & 0x4 ? digitalWrite(led9, HIGH) : digitalWrite(led9, LOW);
}

//private Methods

void Controls::Minus(bool b) {
	if (b) {
		digitalWrite(led8, LOW);
	}
	else {
		digitalWrite(led8, HIGH);
	}
}

void Controls::Decade(bool b) {
	if (b) {
		digitalWrite(led7, LOW);
		digitalWrite(led9, LOW);
	}
	else {
		digitalWrite(led7, HIGH);
		digitalWrite(led9, HIGH);
	}
}

void Controls::setPinModeLed(bool b) {
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

void Controls::NA() {
	setLED(0001000000);
	delay(time / 4);
	LEDon(false);
	delay(time / 4);
	setLED(0001000000);
	delay(time / 4);
	LEDon(false);
	delay(time / 4);
}

