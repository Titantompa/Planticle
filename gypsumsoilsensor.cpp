#include "gypsumsoilsensor.h"

GypsumSoilSensor::GypsumSoilSensor()
{
  readings = 20;

  bias = 1000; // todo: change this!!!

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
  double summedSamples = 0.0;



    setADCSampleTime(ADC_SampleTime_480Cycles);

    double samples[readings*2];

    for(int i = 0; i < readings; i++)
    {
      digitalWrite(A2, HIGH);
      digitalWrite(A1, LOW);

      delay(1);

      samples[i*2] = analogRead(A0);

      // summedSamples += analogRead(A0);

      digitalWrite(A2, LOW);
      digitalWrite(A1, HIGH);

      delay(1);

      samples[(i*2)+1] = 4095-analogRead(A0);
    }

    for(int j = 0; j < readings*2; j++)
    {
      Serial.printf("Sample(%d): %f\r\n", j, samples[j]);
      summedSamples += samples[j];
    }


#if fhfhfhf

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
#endif
    //analogWrite(D0, 0);

    // Turn both pins off
    digitalWrite(A2, LOW);
    digitalWrite(A1, LOW);

    return (summedSamples/(readings*2))/bias;
}
