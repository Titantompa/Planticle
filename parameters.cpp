#include "parameters.h"


#include "application.h"

  bool Parameters::VerifyMemory()
  {
    uint32_t token = 'P' << 25 | 'L' << 16 | 'T' << 8 | '0';
    uint32_t memToken;

    EEPROM.get(0, memToken);

    if(memToken != token)
    {
      // Fill memory with default values
      EEPROM.put(0, token);
      EEPROM.put(sizeof(uint32_t), 500);
      EEPROM.put(sizeof(uint32_t)+sizeof(uint16_t), 30); // 30 seconds
    }

    return true;
  }

  void Parameters::LoadParameters()
  {
    if(VerifyMemory())
    {
        EEPROM.get(sizeof(uint32_t), _substrateBias);
        EEPROM.get(sizeof(uint32_t)+sizeof(uint16_t), _pumpTimeout);
    }
  }

  void Parameters::SaveParameters()
  {
    VerifyMemory();
    EEPROM.put(sizeof(uint32_t), _substrateBias);
    EEPROM.get(sizeof(uint32_t)+sizeof(uint16_t), _pumpTimeout);
  }

  uint16_t Parameters::GetSubstrateBias()
  {
    LoadParameters();
    return _substrateBias;
  }

  void Parameters::SetSubstrateBias(uint16_t bias)
  {
    _substrateBias = bias;
    SaveParameters();
  }

  uint16_t Parameters::GetPumpTimeout()
  {
    LoadParameters();
    return _pumpTimeout;
  }

  void Parameters::SetPumpTimeout(uint16_t timeout)
  {
    _pumpTimeout = timeout;
    SaveParameters();
  }
