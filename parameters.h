#ifndef _PARAMETERS_H
#define _PARAMETERS_H

#include "application.h"

class Parameters
{
private:
  bool VerifyMemory();
  uint16_t _substrateBias;
  uint16_t _pumpTimeout;
  void LoadParameters();
  void SaveParameters();
public:
  uint16_t GetSubstrateBias();
  void SetSubstrateBias(uint16_t bias);
  uint16_t GetPumpTimeout();
  void SetPumpTimeout(uint16_t timeout);
};

#endif
