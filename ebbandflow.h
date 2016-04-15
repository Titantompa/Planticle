#ifndef WATERPUMP_H
#define WATERPUMP_H

#include "application.h"

enum EbbAndFlowState
{
  Ebb,
  Flood
};

enum EbbAndFlowPumpState
{
  Passive = 0,
  Pumping = 1,
  TimedOut = 10,
  Overflowed = 11,
  LowWater = 12
};

class EbbAndFlowSystem {

private:
  pin_t _pumpPin; // D0
  pin_t _overflowSensorPin; // D4
  pin_t _lowSensorPin; // D6
  int32_t _timeout;

  EbbAndFlowState _fillState;
  int32_t _fillStartedTime; // unixtime

public:
  EbbAndFlowSystem(pin_t pumpPin, pin_t overflowSensorPin, pin_t lowSensorPin, int timeout);

  EbbAndFlowPumpState loop();

  void flow();

  void ebb();

  EbbAndFlowState getFillState();
};

#endif
