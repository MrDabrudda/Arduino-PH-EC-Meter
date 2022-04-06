# Arduino-PH-EC-Meter
Arduino PH &amp; EC Meter for hydroponics and gardening

Using an Arduino NANO or just about any Arduino you can create a very accurate PH & EC/TDS meter for hydroponic and gardening.

1) Connect your Arduino to your computer, start the Arduino IDE and flash the AREF_Calibrate.ino to the Arduino.
2) Get an accurate Digital Multi-Meter and measure the voltage on pins AREF and GND
3) Edit the PHEC_Meter.ino and add the voltage from AREF/GND pin to the float iREF = variable.
4) Save and flash PHEC_Meter.ino to your Arduino
5) Disconnect the USB cable from the Arduino and connect the PH, EC, Temperature sensors, and OLED to the following pins:

PH probe connection (E201-BNC):
5v
GND
Po to A0

OLED connection (128x64) I2C display:
5v
GND
SDA to A4
SCL to A5

EC Probe connection (Ocean-TDS Maker Sensor):
S to A1
GND to GND
VCC to +5V

Temperature Probe connection (GIKFUN Temp probe):
Power to +5V
GND to GND
Data to D7

6) Adjust the variable resistor closest to the BNC connector to adjust the PH sensor.  
It will be very helpful to have a PH testing solutions.  I have 4.0, 6.86, and 9.18 PH solutions.

TODO:
Desiging a case to hold all the electronics
