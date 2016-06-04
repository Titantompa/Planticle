#include "gypsumsoilsensor.h"

GypsumSoilSensor::GypsumSoilSensor(Parameters params)
{
  parameters = params;

  readings = 20;
  parameters.LoadParameters();
  bias = parameters.GetSubstrateBias(); // todo: change this!!!

  Serial.printf("Substrate Humidity Sensor Bias: %d\r\n", bias);

  // D3 is output connected directly to soil meter
  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);

  // D5 is output connected to voltage divider
  pinMode(A2, OUTPUT);
  digitalWrite(A2, LOW);
}

double GypsumSoilSensor::readTemperature()
{
  return 0.0;
}

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

      digitalWrite(A2, LOW);
      digitalWrite(A1, HIGH);

      delay(1);

      samples[(i*2)+1] = 4095-analogRead(A0);
    }

    // Turn both pins off
    digitalWrite(A2, LOW);
    digitalWrite(A1, LOW);

    for(int j = 0; j < readings*2; j++)
    {
      // Serial.printf("Sample(%d): %f\r\n", j, samples[j]);
      summedSamples += samples[j];
    }

    double average = summedSamples/(readings*2);
    if(average > bias)
    {
      // Change bias!!
      bias = average+1;
      Serial.printf("Substrate Humidity Sensor Bias: %d\r\n", bias);
      parameters.SetSubstrateBias(bias);
      parameters.SaveParameters();
    }

    return average/bias;
}
