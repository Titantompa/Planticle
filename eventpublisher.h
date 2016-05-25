#ifndef _EVENTPUBLISHER_H
#define _EVENTPUBLISHER_H

#include "application.h"

class EventPublisher
{
private:
  String _deviceName;
public:
  void SetDeviceName(String & deviceName);
  bool PublishEvent(String & eventName, String & data);
};

#endif
