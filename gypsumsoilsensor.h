#ifndef GYSPUMSOILSENSOR_H
#define GYSPUMSOILSENSOR_H
#include "application.h"

class GypsumSoilSensor
{
private:
  int readings;
public:
  GypsumSoilSensor();
  double readTemperature();
  double readMoisture();
};

#endif
