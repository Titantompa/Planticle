#include "parameters.h"


#include "application.h"

  bool Parameters::VerifyMemory()
  {
    uint32_t token = 'P' << 25 | 'T' << 16 | 'L' << 8 | 'E';
    uint32_t memToken;

    EEPROM.get(0, memToken);

    if(memToken != token)
    {
      // Fill memory with default values
      EEPROM.put(0, token);
      EEPROM.put(sizeof(uint32_t), 500);
    }

    return true;
  }

  void Parameters::LoadParameters()
  {
    if(VerifyMemory())
    {
        EEPROM.get(sizeof(uint32_t), _substrateBias);
    }
  }

  void Parameters::SaveParameters()
  {
    EEPROM.put(sizeof(uint32_t), _substrateBias);
  }

  short Parameters::GetSubstrateBias()
  {
    LoadParameters();
    return _substrateBias;
  }

  void Parameters::SetSubstrateBias(short bias)
  {
    _substrateBias = bias;
    SaveParameters();
  }
