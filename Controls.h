/*
@author smon
	3AHEL
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
	
	void setNumber(int n);
	void setLetter(char l);
	void Write(char s[], int length);

	double getPercentage(int n);
	void showPercentage(int n);

	void Color(long n);
	void Mux(int * n);

private:
	bool pin_active;
	bool seg_active;
	bool line_active;
	bool rgb_active;
	
private:
	void NA();
	void setPinModeLed(bool b);
};