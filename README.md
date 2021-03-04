# HTLUnoControls
## Arduino Uno- & HTL Uno Ports:

[![](https://github.com/s-grundner/HTLUnoControls/blob/main/md/ports.jpg)](https://arduino.stackexchange.com/questions/14407/use-all-pins-as-digital-i-o)

---

|****************Methods****************||
|:--------------------------------------|:---|
|void setPins()                         |set IO to pins|
|void setHex(bool-b)                    |set output to hex display|
|void setLine(bool b)                   |set output to led-line|
|void setRgb(bool b)                    |set output to rgb-led|
|void setMode(int n)                    |input a 3-bit binary value referring to the corresponding DDR bits of the Onboard Control pins 12 11 10|
|void ledOn(bool b)                     |outputs HI on pins 0-9|
|void setLed(unsigned long x)           |outputs HI or LO on pins 0-9 according to the user 10-bit binary inpute.i.: setLed(0b000011111) led 0-4 are HI led 5-9 are LO|
|void setNumber(int n)                  |displays a hex number from -31 to 31 if hex display is active or a 10-bit binary number if the led line is active|
|void setLetter(char l)                 |displays alphabet character on hex display|
|void Write(char s[])                   |not yet implemented|
|double getPercentageAnalogIn(int n)    |reads analog input-pin and returns the percentage of the applied voltage while 5V are 100%|
|void showPercentageAnalogIn(int n)     |reads analog input-pin and displays it on the in decades, if the hex display is active, or indicates the percentage on the led-bar if the led-bar is active|
|void showPan(int n)                    | |
|void Color(long n)                     |input RGB-hex value in hex|
|void Mux(int * n)                      |not yet implemented|
|***************************************| | 
---
