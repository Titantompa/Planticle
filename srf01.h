#ifndef SRF01_H
#define SRF01_H

#include "application.h"

enum SRF01Command {
  NoCommand,
  FindRange = 0x51,
  GetResult = 0x5E
};

class SRF01 {
private:

  time_t _commandTime;

  void sendCommand(uint8_t address, uint8_t command);
  void sendBreak();
  void setupSerial1();

  SRF01Command _command = NoCommand;

public:

  int Timestamp;
  int Range;

  SRF01();

  void loop();

  void findRange();
};



#endif
