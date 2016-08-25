/*
arduinoTSIC506F_Test - A test programm fo the TSIC506F temperature sensor
Copyright (C) 2016-2016 Simon Wyss <wysi94@gmail.com>

This file is part of arduinoTSIC506F_Test.

arduinoTSIC506_Test is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

arduinoTSIC506F_Test is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the Lesser
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with arduinoTSIC506F_Test.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
	LiquidCrystal Library 
	The LiquidCrysta library works with all LCD displays that are compatible with the 
	Hitachi HD44780 driver. There are many of them out there, and you
	can usually tell them by the 16-pin interface.
 
	This sketch prints "Hello World!" to the LCD
	and shows the time.
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */


#include "TSIC.h"	// TSIC temperature sensor library

#include "LiquidCrystal.h"
//#include <LCDKeypad.h> //modifies LiquidCrystal.h, adds right pin config.

//LCDKeypad lcd;
//LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7); //works (RW-PIN = 13)
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); //works
//(RW-PIN of sainsmart LCD Keypad is tied to GND)
//it makes no sense to use the constructor with the PIN 13 (because it is on GND)

//TSIC
/*
TSIC Sensor1(30, 31);    // Signalpin, VCCpin
TSIC Sensor2(34, 35);    // Signalpin, VCCpin
TSIC Sensor3(38, 39);    // Signalpin, VCCpin
TSIC Sensor4(42, 43);    // Signalpin, VCCpin
*/
TSIC Sensor1(30);    // Signalpin, VCCpin
TSIC Sensor2(34);    // Signalpin, VCCpin
TSIC Sensor3(38);    // Signalpin, VCCpin
TSIC Sensor4(42);    // Signalpin, VCCpin

uint16_t temperature = 0;
float Temperatur_C = 0;

uint16_t temperature2 = 0;
float Temperatur_C2 = 0;

uint16_t temperature3 = 0;
float Temperatur_C3 = 0;

uint16_t temperature4 = 0;
float Temperatur_C4 = 0;

//median
float temp_c = 0;
float temp_c2 = 0;
float temp_c3 = 0;
float temp_c4 = 0;

int meas_count = 10;

void setup(void) {
 
	Serial.begin(9600);
	Serial.println(F("Arduino TSIC Test"));
	
	// set up the LCD's number of columns and rows: 
	lcd.begin(16, 2);
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("Temp");
	
	pinMode(31,OUTPUT);
	pinMode(35,OUTPUT);
	pinMode(39,OUTPUT);
	pinMode(43,OUTPUT);

	digitalWrite(31,HIGH);
	digitalWrite(35,HIGH);
	digitalWrite(39,HIGH);
	digitalWrite(43,HIGH);
	
	delay(85);
	
	if (Sensor1.getTemperture(&temperature) == 0) {
		Temperatur_C = Sensor1.calc_CelsiusTsic506(&temperature);
		temp_c = Temperatur_C;
	}
	if (Sensor2.getTemperture(&temperature2) == 0) {
		Temperatur_C2 = Sensor2.calc_CelsiusTsic506(&temperature2);
		temp_c2 = Temperatur_C;
	}
	if (Sensor3.getTemperture(&temperature3) == 0) {
		Temperatur_C3 = Sensor3.calc_CelsiusTsic506(&temperature3);
		temp_c3 = Temperatur_C;
	}
	if (Sensor4.getTemperture(&temperature4) == 0) {
		Temperatur_C4 = Sensor4.calc_CelsiusTsic506(&temperature4);
		temp_c4 = Temperatur_C;
	}
	
	
}

void loop(void) {

	digitalWrite(31,HIGH);
	digitalWrite(35,HIGH);
	digitalWrite(39,HIGH);
	digitalWrite(43,HIGH);
	
	delay(85);
	/*
	temp_c = 0;
	temp_c2 = 0;
	temp_c3 = 0;
	temp_c4 = 0;
	*/
	//for(int i = 0; i < meas_count; i++){
		if (Sensor1.getTemperture(&temperature) == 0) {
			Temperatur_C = Sensor1.calc_CelsiusTsic506(&temperature);
			temp_c = (temp_c*9.0 + Temperatur_C)/10;
		}
		if (Sensor2.getTemperture(&temperature2) == 0) {
			Temperatur_C2 = Sensor2.calc_CelsiusTsic506(&temperature2);
			temp_c2 += (temp_c2*9.0 + Temperatur_C2)/10;
		}
		if (Sensor3.getTemperture(&temperature3) == 0) {
			Temperatur_C3 = Sensor3.calc_CelsiusTsic506(&temperature3);
			temp_c3 += (temp_c3*9.0 + Temperatur_C3)/10;
		}
		if (Sensor4.getTemperture(&temperature4) == 0) {
			Temperatur_C4 = Sensor4.calc_CelsiusTsic506(&temperature4);
			temp_c4 += (temp_c4*9.0 + Temperatur_C4)/10;
		}
	//}
	/*
	temp_c = temp_c / 10;
	temp_c2 = temp_c2 / 10;
	temp_c3 = temp_c3 / 10;
	temp_c4 = temp_c4 / 10;
	*/
	
	digitalWrite(31,LOW);
	digitalWrite(35,LOW);
	digitalWrite(39,LOW);
	digitalWrite(43,LOW);
	
		Serial.print("Temperaturen: ");
		Serial.print(Temperatur_C);
		Serial.print("  ");
		Serial.print(Temperatur_C2);
		Serial.print("  ");
		Serial.print(Temperatur_C3);
		Serial.print("  ");
		Serial.print(Temperatur_C4);
		Serial.println(" ");
		
		//LCD print:
		lcd.setCursor(0,0);
		//lcd.print("T1 ");
		lcd.print(Temperatur_C);
		
		lcd.setCursor(8,0);
		//lcd.print("T2 ");
		lcd.print(Temperatur_C2);
		
		lcd.setCursor(0,1);
		//lcd.print("T3 ");
		lcd.print(Temperatur_C3);
		
		lcd.setCursor(8,1);
		//lcd.print("T4 ");
		lcd.print(Temperatur_C4);
	delay(1000);    // wait 1 seconds
}

