/*
@author smon
	3AHEL
*/

#pragma once

#include "Arduino.h"

#define time 500
#define muxTime 5

#define led0 0		//Port D
#define led1 1		//Port D
#define led2 2		//Port D
#define led3 3		//Port D
#define led4 4		//Port D
#define led5 5		//Port D
#define led6 6		//Port D
#define led7 7		//Port D
#define led8 8		//Port B
#define led9 9		//Port B
#define led10 10	//Port B
#define led11 11	//Port B
#define led12 12	//Port B
#define led13 13	//Port B

#define analog0 14	//Port C
#define analog1 15	//Port C
#define analog2 16	//Port C 
#define analog3 17	//Port C
#define analog4 18	//Port C
#define analog5 19	//Port C

#define seg 10		//Port B
#define line 11		//Port B
#define rgb 12		//Port B

class Controls {
public:
	Controls();

	void setPins();
	void setHex(bool b);
	void setLine(bool b);
	void setRgb(bool b);

	void setMode(int n);					//input a 3-bit binary value referring to the corresponding DDR bits of the Onboard Control pins 12 11 10
	int getMode();							//returns a 3-bit value which is cut out from the DDR onboard-control section e.i.: getMode(0b000 000 00) the 3 standalone bits equals the return value

	void ledOn(bool b);						//outputs HI on pins 0-9
	void setLed(unsigned long x);			//outputs HI or LO on pins 0-9 according to the user 10-bit binary input e.i.: setLed(0b000011111) led 0-4 are HI led 5-9 are LO
	
	void setNumber(int n);					//displays a hex number from -31 to 31 if hex display is active or a 10-bit binary number if the led line is active
	void setLetter(char l); 				//displays alphabet character on hex display
	void Write(char s[]);					//not yet implemented

	double getPercentageAnalogIn(int n);	//reads analog input-pin and returns the percentage of the applied voltage while 5V are 100%
	void showPercentageAnalogIn(int n);		//reads analog input-pin and displays it on the in decades, if the hex display is active, or indicates the percentage on the led-bar if the led-bar is active
	void showPan(int n);

	void Color(long n);						//input RGB-hex value in hex
	void Mux(int * n);						//not yet implemented

private:
	bool pin_active;
	bool seg_active;
	bool line_active;
	bool rgb_active;
	
private:
	void NA();
	void setPinModeLed(bool b);
	void modeAct(int n);
};
