/*
 * https://www.youtube.com/watch?v=a4zfBkQ4LcE
 * https://www.youtube.com/watch?v=ofZ7D8lVsXM
 * https://www.youtube.com/watch?v=nf3aXpXo_sY
 */
#include <OneWire.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

Adafruit_SSD1306 display(-1);

//AREF pin voltage measured using digital multi meter.
//Must run AREF_Calibrate.ino to get this value.
float iREF = 1.064;

namespace pin {
  const byte tds_sensor = A1;
  const byte one_wire_bus = 7;
}

namespace sensor {
  float ec = 0;
  unsigned int tds = 0;
  float waterTemp = 0;
  float ecCalibration = 1;
  }

OneWire oneWire(pin::one_wire_bus);
DallasTemperature dallasTemperature(&oneWire);

void setup() {
  Serial.begin(9600);
  dallasTemperature.begin();
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  analogReference(INTERNAL); //1.1v ADC internal reference
  delay(5);
}

void loop() {
  int measure = analogRead(A0);
  
  double voltage = fReadVcc() / 1024.0 * measure; //classic digital to voltage conversion
  float Po = 7 + ((2.5 - voltage) / 0.18);
  
  readTdsQuick();
  delay(1000);

  display.clearDisplay();
  display.display();
  display.setTextColor(WHITE);
  display.setTextSize(2);

  display.setCursor(0,0);
  display.print("PH:");
  display.print(Po, 3);
  display.display();

  display.setCursor(0,17);
  display.print("EC:");
  display.print(sensor::ec, 2);
  display.display();

  display.setCursor(0,34);
  display.print("TDS:");
  display.print(sensor::tds);
  display.display();

  display.setCursor(0,51);
  display.print("TEMP:");
  display.print(sensor::waterTemp, 2);
  display.display();
  delay(2000);

  /*
  Serial.print("PH: ");
  Serial.println(Po, 3);
  
  Serial.print("Voltage from analog PH probe: ");
  Serial.println(voltage, 3);
     
  Serial.print("Measured input voltage from USB cable: ");
  Serial.println(fReadVcc());
  Serial.print("");
  */
}

void readTdsQuick() {
  dallasTemperature.requestTemperatures();
  sensor::waterTemp = dallasTemperature.getTempCByIndex(0);
  //float rawEc = analogRead(pin::tds_sensor) * iREF / 1024;
  float rawEc = fReadVcc() / 1024 * analogRead(pin::tds_sensor);
      
  float temperatureCoefficient = 1.0 + 0.02 * (sensor::waterTemp -25.0);
  sensor::ec = (rawEc / temperatureCoefficient) * sensor::ecCalibration;
  sensor::tds = (133.42 * pow(sensor::ec, 3) -255.86 * sensor::ec *sensor::ec + 857.39 * sensor::ec) * 0.5;
  /*
  Serial.print(F("TDS:")); Serial.println(sensor::tds);
  Serial.print(F("EC:")); Serial.println(sensor::ec, 2);
  Serial.print(F("Temperature:")); Serial.println(sensor::waterTemp, 2);
  Serial.println();
  */
}

//function used for internal reference value of the 328p (~1.1v) to calculate the VCC value which comes from USB/power supply
double fReadVcc() {
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(30);
  ADCSRA |= _BV(ADSC); //Start ADC conversion
  while (bit_is_set(ADCSRA,ADSC)); //wait until conversion is complete
  int result = ADCL; //get first half of result
  result |=ADCH<<8; //get rest of the result
  float batVolt = (iREF / result) * 1024; //use the known iRef to calculate battery voltage
  return batVolt;
}
