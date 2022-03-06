# HTLUnoControls
## Arduino Uno- & HTL Uno Ports:

[![Pins and Ports of the Arduino Uno](https://github.com/s-grundner/HTLUnoControls/blob/main/md/ports.jpg)](https://arduino.stackexchange.com/questions/14407/use-all-pins-as-digital-i-o)

---

| Methods||
|:------------------------------------------|:---|
| void setPins()                            |set IO to pins|
| void setHex(bool b)                       |set output to hex display|
| void setLine(bool b)                      |set output to led-line|
| void setRgb(bool b)                       |set output to rgb-led|
| void setMode(int n)                       |input a 3-bit binary value referring to the corresponding DDR bits of the Onboard Control pins 12 11 10|
| void ledOn(bool b)                        |outputs HI on true and LO on false at pins 0-9|
| void setOut(unsigned long x)              |outputs HI or LO on pins 0-9 according to the user 10-bit binary input. I.e.: setLed(0b0000011111) led 0-4 are HI led 5-9 are LO|
| void setNumber(int n)                     |displays a hex number from -31 to 31 if hex display is active or a 10-bit binary number if the led line is active|
| void setLetter(char l)                    |displays alphabetic characters on hex display|
| void write(char s[], int len)             |writes a string to the hex display|
| double getPercentageAnalogIn(int n)       |reads analog input-pin and returns the percentage of the applied voltage where 5V are 100%|
| void showPercentageAnalogIn(int n)        |reads analog input-pin and displays it on the in decades, if the hex display is active, or indicates the percentage on the led-bar if                                              the led-bar is active|
| void showPan(int n)                       |use analog input for panning the led-line or hex-display|
| void color(long n)                        |input RGB-hex value in hex|
| void mux(int * n)                         |_not yet implemented_|
|*******************************************| | 
---
