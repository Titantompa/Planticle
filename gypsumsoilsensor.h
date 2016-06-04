#ifndef GYSPUMSOILSENSOR_H
#define GYSPUMSOILSENSOR_H
#include "application.h"
#include "parameters.h"

class GypsumSoilSensor
{
private:
  int bias;
  int readings;
  Parameters * parameters;
public:
  GypsumSoilSensor(Parameters * params);
  double readTemperature();
  double readMoisture();
};

#endif
