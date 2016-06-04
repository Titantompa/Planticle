#ifndef _PARAMETERS_H
#define _PARAMETERS_H

#include "application.h"

class Parameters
{
private:
  bool VerifyMemory();
  short _substrateBias;
  void LoadParameters();
  void SaveParameters();
public:
  short GetSubstrateBias();
  void SetSubstrateBias(short bias);
};

#endif
