#include "ebbandflow.h"
#include "time.h"

EbbAndFlowSystem::EbbAndFlowSystem(pin_t pumpPin, pin_t overflowSensorPin, pin_t lowSensorPin, int timeout)
{
  _pumpPin = pumpPin;
  _overflowSensorPin = overflowSensorPin;
  _lowSensorPin = lowSensorPin;
  _timeout = timeout;

  // Configure pins
  pinMode(_overflowSensorPin, INPUT);
  pinMode(_lowSensorPin, INPUT_PULLUP);
  pinMode(_pumpPin, OUTPUT);
}

EbbAndFlowState EbbAndFlowSystem::getFillState()
{
  return _fillState;
}

void EbbAndFlowSystem::flow()
{
  _fillState = Flood;

  _fillStartedTime = Time.now();

  // Start the pump
  // digitalWrite(_pumpPin, HIGH);
  analogWrite(_pumpPin, 75, 40000); // 16,12000
}

void EbbAndFlowSystem::ebb()
{
  // Stop the pump
  //digitalWrite(_pumpPin, LOW);
  analogWrite(_pumpPin, 0);

  _fillState = Ebb;
}

EbbAndFlowPumpState EbbAndFlowSystem::loop()
{
  // If we aren't in a flood cycle, do nothing
  if(_fillState == Ebb)
    return Passive;

  if(digitalRead(_overflowSensorPin) == LOW) // Check the overflow sensor
  {
    Serial.println("Overflow sensor triggered, stopping flood");
    ebb();
    return Overflowed;
  }
  else if(digitalRead(_lowSensorPin) == LOW) // Check the low level sensor
  {
    Serial.println("Low water level sensed, stopping flood");
    ebb();
    return LowWater;
  }
  else if(Time.now()-_fillStartedTime >= _timeout)  // Check the time
  {
    Serial.println("Flood has been going on for longer than permitted, stopping flood");
    ebb();
    return TimedOut;
  }

  return Pumping;
}
