// Jens Arduino Pedals
// This car simulator pedals program have gas, brake and clutch to connect to usb port.
// No extra drives need to be installed in windows to get this to work.
//
// NOTE: This file is for use with Arduino Leonardo and  Arduino Micro only.
//       Arduino Micro only.
//
// To get this program to work you need MHeironimus GPLv3 joystick libary from
// https://github.com/MHeironimus/ArduinoJoystickLibrary version-1.0
//
// by Jens Söderström jensws.com
// 2016-11-01
//
// This project is licensed under the terms of the GNU V.3 license.
//
//--------------------------------------------------------------------


#include <Joystick.h>

Joystick_ Pedals(
  JOYSTICK_DEFAULT_REPORT_ID, //hidReportId
  JOYSTICK_TYPE_GAMEPAD, //joystickType
  0, //buttonCount 
  0, //hatSwitchCount
  true, //includeXAxis -> Gas
  true, //includeYAxis -> Brake
  true, //includeZAxis -> Clutch
  false, //includeRxAxis 
  false, //includeRyAxis 
  false, //includeRzAxis
  false, //includeRudder 
  false, //includeThrottle 
  false, //includeAccelerator 
  false, //includeBrake 
  false); //includeSteering

// Variable
int gas = A0;
int brake = A1; 
int clutch = A3;
int gasValue = 0;
int gasValuebyte = 0;
int brakeValue = 0;
int brakeValuebyte1 = 0;
int brakeValuebyte2 = 0;
int clutchValue = 0;
int clutchValuebyte1 = 0;
int clutchValuebyte2 = 0;
int clutchValue5V = 512;
// init joystick libary
void setup() {
  Pedals.begin();
  Serial.begin(9600);
}

void loop() {
  
  // Gas
  gasValue = analogRead(gas);
  if (gasValue >= 1) {
  gasValuebyte = gasValue / 4 ;
   }
   else
   {
    gasValuebyte = 0 ;
   }
  Pedals.setXAxis(gasValuebyte);
  delay(1); 

  // Brake
  brakeValue = analogRead(brake);
  if (brakeValue >= 1) {
    brakeValuebyte1 = brakeValue / 4;
    brakeValuebyte2 = brakeValuebyte1 - 127;
  
   }
   else
   {
    brakeValuebyte2 = -127;
   }
  Pedals.setYAxis(brakeValuebyte2);
  delay(1); 

  // Clutch
  clutchValue = analogRead(clutch);
  if (clutchValue >= 1) {
  clutchValuebyte1 = clutchValue / 4;
  clutchValuebyte2 = clutchValuebyte1 - 127;
  clutchValue5V = clutchValue - 500;
   }
   else
   {
    clutchValuebyte2 = -127;
   }

   if (clutchValue > 512) {
    clutchValue5V = clutchValue - 512; 
   }
   else
   {
    clutchValue5V = 0;
   }
   Pedals.setZAxis(clutchValue5V);
   Serial.println(clutchValue);
   //Serial.println(clutchValue5V);
  delay(1); 
}
