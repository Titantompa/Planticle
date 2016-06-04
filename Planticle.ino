#include "am2302.h"
#include "gypsumsoilsensor.h"
#include "ebbandflow.h"
#include "srf01.h"

double Humidity = 0.0;
double Temperature = 0.0;
double Substrate = 0.0;
int Overflow = 1234;
int PumpStatus = 0;

DHT theSensor(6, AM2302);

GypsumSoilSensor soilSensor;

EbbAndFlowSystem ebbAndFlow(D0, D3, D4, 80); // 50

SRF01 rangeFinder;

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

String DeviceName;

// Open a serial terminal and see the device name printed out
void NameHandler(const char *topic, const char *data) {
  DeviceName = String(data);

  Serial.println("received " + String(topic) + ": " + DeviceName);
}

bool waitingForRange = false;
bool aquiringRange = false;
int lastRangeTimestamp = 0;

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

  // Serial1.begin(9600);
  // Serial1.halfduplex(true);

  waitingForRange = false;
  aquiringRange = false;
  lastRangeTimestamp = 0;

  Serial.begin(9600);

  Particle.subscribe("spark/", NameHandler);
  Particle.publish("spark/device/name");
}






void loop()
{
#if hallaboink
  if(!aquiringRange)
  {
    // Uppdatera var 5:e sekund
    if(rangeFinder.Timestamp + 5 < Time.now())
    {
      rangeFinder.findRange();
      aquiringRange = true;
    }
  }
  else
  {
    rangeFinder.loop();

    if(rangeFinder.Timestamp + 5 > Time.now())
      aquiringRange = false;
  }

  delay(100);
#endif

Substrate = soilSensor.readMoisture();

Serial.printf("Moisture: %f\r\n", Substrate);


delay(2000);


#if fghhhhhh
  if(ebbAndFlow.getFillState() == Ebb)
  {
    Serial.println("Device: " + DeviceName);

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
  #endif
}
