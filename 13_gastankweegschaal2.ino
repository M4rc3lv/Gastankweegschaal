// Versie 2.0 11-8-2016: Schakelaars LEEG en VOL (Tarra) toegevoegd

#include <Arduino.h>
#include "HX711.h"
#include "LedControl7.h"
#include <EEPROM.h>

HX711 scale(A1, A0); // DOUT, SCK

#define ANALOG_UIT 2

// 8-digit LED-display (waarvan 4 digits in gebruik)
#define DIN 4
#define CLK 5
#define CS 10
#define NBR_MTX 1
LedControl7 Segment7 = LedControl7(DIN, CLK, CS, NBR_MTX);

#define TARRA_LEEG 3
#define TARRA_VOL 8

#define EEPROM_VOL 1000
#define EEPROM_LEEG 1010

float TarraVol,TarraLeeg;

void setup() {
	Serial.begin(115200);
	TarraVol=readFloat(EEPROM_VOL);
	if(TarraVol==0) TarraVol=10;
	TarraLeeg=readFloat(EEPROM_LEEG);
	if(TarraLeeg==0) TarraLeeg=1;
	
 pinMode(TARRA_LEEG, INPUT_PULLUP);
 pinMode(TARRA_VOL, INPUT_PULLUP);
	 
 scale.set_scale(1); 

 for (int i = 0; i < NBR_MTX; i++) {
  Segment7.shutdown(i, false);
  Segment7.setIntensity(i, 10);
  Segment7.clearDisplay(i);
 }

 Serial.print("TarraLeeg=");Serial.println(TarraLeeg);
 Serial.print("TarraVol=");Serial.println(TarraVol);
}

void loop() {  
  double g = scale.get_units(10);
  Serial.print("Scale=");Serial.println(g);
  if(g>TarraVol) g=TarraVol;
  if(g<TarraLeeg) g=TarraLeeg;
  double procent = mapf(g,TarraLeeg, TarraVol, 0,99);
  ToonProcent((int)procent);

  long t = millis();
  while(abs(millis()-t)<500) {
  	if(digitalRead(TARRA_VOL)==LOW) {HandleVol(); break;}
  	if(digitalRead(TARRA_LEEG)==LOW) {HandleLeeg(); break;}
   delay(10);
  }  
}

void HandleVol() {
	Serial.println("VOL");	
 Segment7.shutdown(0, false);
 Segment7.setDigit(0, 1, (byte)9, false);
 Segment7.setDigit(0, 2, (byte)9, false);
 Segment7.setDigit(0, 3, (byte)9, false);
 Segment7.setDigit(0, 4, (byte)9, false);
 float f = scale.get_units(10);
 writeFloat(EEPROM_VOL,f);
 TarraVol=f;
 delay(200);
 Segment7.clearDisplay(0);
}

void HandleLeeg() {
	Serial.println("LEEG"); 
 Segment7.shutdown(0, false);
 Segment7.setDigit(0, 1, (byte)0, false);
 Segment7.setDigit(0, 2, (byte)0, false);
 Segment7.setDigit(0, 3, (byte)0, false);
 Segment7.setDigit(0, 4, (byte)0, false);
 float f = scale.get_units(10);
 writeFloat(EEPROM_LEEG,f);
 TarraLeeg=f;
 delay(200);
 Segment7.clearDisplay(0);
}

void ToonProcent(int procent) {
 Segment7.shutdown(0, false);
 Segment7.setDigit(0, 1, (byte)(procent % 10), false);
 Segment7.setDigit(0, 2, (byte)((procent / 10) % 10), false);
 Serial.print("Procent: "); Serial.println(procent);
}

float readFloat(unsigned int addr) {
	float f;
	EEPROM.get(addr,f);
	return f;
}

void writeFloat(unsigned int addr, float x){
 EEPROM.put(addr,x);
}

float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


