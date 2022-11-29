#include <Arduino.h>

const int SoilHumiditySensorPin = A0;
float soil_humidity;
int analogSoloSeco = 1024;
int analogSoloMolhado = 835;
int percSoloSeco = 0;
int percSoloMolhado = 100;

float getSoilHumidity()
{
    //Serial.println(analogRead(SoilHumiditySensorPin));
    soil_humidity = constrain(analogRead(SoilHumiditySensorPin), analogSoloMolhado, analogSoloSeco);
    soil_humidity = map(soil_humidity, analogSoloMolhado, analogSoloSeco, percSoloMolhado, percSoloSeco);
    soil_humidity = (soil_humidity) / 100;
    return soil_humidity;
}
