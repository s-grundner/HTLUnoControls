/*
HTL Uno Controls
including:
*switching Modes between RGB, LED Line & 10 Segment display...
*controlling individual LEDs...
*Multiplexing Modes...
*controlling character displayment...
*controlling the LED Line...
*display poti status...
*RGB colors...

>further information in the command.txt file

-GruS
*/

#include "Arduino.h"

#define time 500
#define muxTime 5

#define pot_correction 0.62

#define led0 0
#define led1 1
#define led2 2
#define led3 3
#define led4 4
#define led5 5
#define led6 6
#define led7 7
#define led8 8
#define led9 9
#define led10 10
#define led11 11
#define led12 12
#define led13 13

#define analog0 14
#define analog1 15
#define analog2 16 
#define analog3 17
#define analog4 18
#define analog5 19

#define seg 10
#define line 11
#define rgb 12

class Controls {
public:
	Controls();

	void setMode(int n);

	void LEDon(bool b);
	void setLED(unsigned long x);
	
	void setByte(int n);
	void setIntByte(int n);
	void setNumber(int n);
	void setLetter(char l);
	void Write(char s[], int length);

	double getPercentage(int n);
	void showPercentage(int n);

	void Color(int n);

	void Mux(int n[]);

private:
	bool pin_active;
	bool seg_active;
	bool line_active;
	bool rgb_active;
	
private:
	void NA();
	void Minus(bool b);
	void Decade(bool b);
	void setPinModeLed(bool b);
};
