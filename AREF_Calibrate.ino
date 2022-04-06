/*
 * Flash sketch to your Arduino and measure AREF and GND pins
 * with a digital multimeter.  
 * 
 * Enter this value into the iREF variable in the 
 * PH_Meter.ino sketch, save and flash PH_Meter.ino to Arduino.
 * Digital multi-meter should read ~1.1v
 */

void setup() {
  // put your setup code here, to run once:
analogReference(INTERNAL);  //set ADC reference to internal 1.1v
}

void loop() {
  // put your main code here, to run repeatedly:
analogRead(A0); //read from pin A0
}
