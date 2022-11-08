#include <SensorWaterflow.h>
#include <Arduino.h>
volatile byte pulseCount = 0;

void IRAM_ATTR pulseCounter()
{
    pulseCount++;
}

SensorWaterflow::SensorWaterflow(int pin)
{
    this->pin = pin;
    pinMode(this->pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(this->pin), pulseCounter, FALLING);
}

void SensorWaterflow::loop()
{
    this->curMillis = millis();

    if (this->curMillis - this->prevMillis > this->refreshRate)
    {
        // Because this loop may not complete in exactly 1 second intervals we calculate
        // the number of milliseconds that have passed since the last execution and use
        // that to scale the output. We also apply the calibrationFactor to scale the output
        // based on the number of pulses per second per units of measure (litres/minute in
        // this case) coming from the sensor.
        this->flowRate = ((1000.0 / (this->curMillis - this->prevMillis)) * pulseCount) / this->calibrationFactor;
        pulseCount = 0;
        this->prevMillis = this->curMillis;
    }
}

float SensorWaterflow::getFlowRate()
{
    return this->flowRate;
}
