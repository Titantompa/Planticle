#include "gypsumsoilsensor.h"

GypsumSoilSensor::GypsumSoilSensor()
{
  readings = 20;

  //pinMode(D0, OUTPUT);
  //digitalWrite(D0, LOW);

  // D3 is output connected directly to soil meter
  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);
  // D5 is output connected to voltage divider
  pinMode(A2, OUTPUT);
  digitalWrite(A2, LOW);
}

double GypsumSoilSensor::readTemperature()
{ return 0.0; }

double GypsumSoilSensor::readMoisture()
{
    setADCSampleTime(ADC_SampleTime_480Cycles);

    double summedSamples = 0.0;

    //analogWrite(D0, 32, 10000);

    for(int i = 0; i < readings; i++)
    {
      digitalWrite(A2, HIGH);
      digitalWrite(A1, LOW);

      delay(200);

      summedSamples += analogRead(A0);

      digitalWrite(A2, LOW);
      digitalWrite(A1, HIGH);

      delay(200);

      summedSamples += 4095-analogRead(A0);
    }

    //analogWrite(D0, 0);

    // Turn both pins off
    digitalWrite(A2, LOW);
    digitalWrite(A1, LOW);

    return (summedSamples/readings)/8191;
}
