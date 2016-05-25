#include "srf01.h"

SRF01::SRF01()
{
  Timestamp = Time.now();
  _command = NoCommand;
  setupSerial1();
}

void SRF01::setupSerial1()
{
  Serial1.begin(9600);
  Serial1.halfduplex(true);
}

void SRF01::sendBreak()
{
  Serial1.end();

  pinMode(TX, OUTPUT);
  digitalWrite(TX, LOW);

  delay(10);

  setupSerial1();

  delay(10);
}

void SRF01::sendCommand(uint8_t address, uint8_t command)
{
  sendBreak();
  Serial1.write(address); // Address
  Serial1.write(command); // Real range cm
}

void SRF01::loop()
{
  if(_command == NoCommand)
    return;

  switch(_command)
  {
    case FindRange:

      // Just in case we've wrapped the millis timer
      if(_commandTime > millis())
        _commandTime = millis();

      // We need to wait 70ms before trying to receive the result from the sonar
      if(_commandTime + 70 > millis())
        break;

      // We simply discard anything the sonar is sending us
      while(Serial1.available())
      {
        int inByte = Serial1.read();
        Serial.println(inByte, HEX);
      }

      // Send command to fetch result
      sendCommand(0x1, 0x5E);

      _command = GetResult;
    break;
    case GetResult:
      // Wait until both bytes are available
      if(Serial1.available() < 2)
        break;

      Serial.println("Received result");
      while(Serial1.available())
      {
        int inByte = Serial1.read();
        Serial.println(inByte, HEX);
      }

      Timestamp = Time.now();

      _command = NoCommand;

    break;
  }
}

void SRF01::findRange()
{
  Serial.println("SRF01::findRange()");

  sendCommand(0x1, 0x51);

  _command = FindRange;
  _commandTime = millis();
}
