#include "am2302.h"
#include "gypsumsoilsensor.h"
#include "ebbandflow.h"

double Humidity = 0.0;
double Temperature = 0.0;
double Substrate = 0.0;
int Overflow = 1234;
int PumpStatus = 0;

DHT theSensor(6, AM2302);

GypsumSoilSensor soilSensor;

EbbAndFlowSystem ebbAndFlow(D0, D3, D4, 80); // 50

int Irrigate(String command)
{
  ebbAndFlow.flow();

  return 1;
}

int Stop(String command)
{
  ebbAndFlow.ebb();

  return 1;
}

void setup() {
  Particle.variable("Humidity", Humidity);
  Particle.variable("Temperature", Temperature);
  Particle.variable("Substrate", Substrate);
  Particle.variable("Overflow", Overflow);
  Particle.variable("PumpStatus", PumpStatus);

  Particle.function("Irrigate", Irrigate);
  Particle.function("Stop", Stop);

  theSensor.begin();

  setADCSampleTime(ADC_SampleTime_144Cycles);

  pinMode(D7, OUTPUT);
  digitalWrite(D7, LOW);
  pinMode(D3, INPUT);

  Serial.begin(9600);
}

void loop() {

  if(ebbAndFlow.getFillState() == Ebb)
  {
    digitalWrite(D7, HIGH);

    Humidity = theSensor.readHumidity();

    Serial.printf("Humidity: %f\r\n", Humidity);

    Temperature = theSensor.readTemperature();

    Serial.printf("Temperature: %f\r\n", Temperature);

    Substrate = soilSensor.readMoisture();

    Serial.printf("Moisture: %f\r\n", Substrate);

    if(digitalRead(D3) == HIGH)
    {
      Serial.println("Overflow sensor idle");
      Overflow = 0;
    }
    else
    {
      Serial.println("Overflow sensor triggered");
      Overflow = 1;
    }


    Serial.println("----------------------------------------");

    digitalWrite(D7, LOW);

    delay(5000);
  }
  else
  {
      PumpStatus = ebbAndFlow.loop();

      delay(10);
  }
}
