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

#include "TSIC.h"	// TSIC temperature sensor library

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
// #define LCD_CS A3 // Chip Select goes to Analog 3
// #define LCD_CD A2 // Command/Data goes to Analog 2
// #define LCD_WR A1 // LCD Write goes to Analog 1
// #define LCD_RD A0 // LCD Read goes to Analog 0

// #define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin


//TSIC
TSIC Sensor1(22, 23);    // Signalpin, VCCpin
TSIC Sensor2(24, 25);    // Signalpin, VCCpin

uint16_t temperature = 0;
float Temperatur_C = 0;

uint16_t temperature2 = 0;
float Temperatur_C2 = 0;


void setup(void) {
 
	Serial.begin(9600);
	Serial.println(F("Arduino TSIC Test"));
	

}

void loop(void) {

	if (Sensor1.getTemperture(&temperature)) {
    Temperatur_C = Sensor1.calc_Celsius(&temperature);
    Serial.print("Temperature: ");
    Serial.print(Temperatur_C);
    Serial.println(" °C");
  }

  delay(1000);    // wait 1 seconds
}

