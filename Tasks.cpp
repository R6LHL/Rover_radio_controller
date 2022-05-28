#include "Tasks.h"

#include <Arduino.h>
#include "config.h"
#include "variables.h"
#include <LoRa.h> // API https://github.com/sandeepmistry/arduino-LoRa/blob/master/API.md

void Tasks::checkJoystick(void){
	currX = joystick.readX();
	currY = joystick.readY();
	currButton = joystick.readButton();

	TaskManager::SetTask_(printJoystick, 0);
	TaskManager::SetTask_(transmitTelemetry,0);
	TaskManager::SetTask_(checkJoystick, JOYSTICK_READ_INTERVAL_MS);
}
//////////////////////////////////////////////////////////////////////////////

void Tasks::printJoystick(void){
	
	Serial.print(F("Joystick X="));
	Serial.println(currX);
	
	Serial.print(F("Joystick Y="));
	Serial.println(currY);
	
	Serial.print(F("Joystick Button="));
	Serial.println(currButton);
}
//////////////////////////////////////////////////////////////////////////////

void Tasks::transmitTelemetry(void)
{
#if DEBUG_MODE == ENABLED  
  Serial.print(F("Sending data...\0"));
#endif

  LoRa.beginPacket();
  LoRa.print(currX);
  LoRa.print(currY);
  LoRa.print(currButton);
  LoRa.endPacket(async_mode);
  
#if DEBUG_MODE == ENABLED  
  Serial.println(F("Done!\0"));
  Serial.println();
#endif
}
//////////////////////////////////////////////////////////////////////////////