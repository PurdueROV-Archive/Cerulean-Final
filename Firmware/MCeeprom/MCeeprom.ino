/****************************************************************************************************************************************
 * Motor Controller EEPROM Programmer
 * Purdue IEEE ROV 2014
 * Nick Molo
 * 
 * This program flushes the eeprom, writing default values to all locations, then writes the specific address defined to address 0.
 *
 ***************************************************************************************************************************************/

#include <EEPROM.h>

#define ADDRESS 0x01

#define LED 8

void setup(){
  
  pinMode(LED, OUTPUT);
 
  //flush eeprom
  for (int i = 0; i < 255; i++){
    EEPROM.write(i, 0xFF);
  }
  
  //program eeprom to address
  EEPROM.write(0, ADDRESS);
 
}

void loop(){ 
  digitalWrite(LED,HIGH);
  delay(100);
  digitalWrite(LED,LOW);
  delay(100);
}
