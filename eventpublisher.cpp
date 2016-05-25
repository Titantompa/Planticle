#include "eventpublisher.h"

void EventPublisher::SetDeviceName(String & deviceName)
{
  _deviceName = deviceName;
}

bool EventPublisher::PublishEvent(String & eventName, String & data)
{
  if(_deviceName.length() == 0)
    return false;

  Particle.publish(_deviceName+"/"+eventName, data);
}
