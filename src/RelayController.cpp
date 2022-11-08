#include <RelayController.h>
#include <Arduino.h>
#include <App.h>

RelayController::RelayController(int pin)
{
    this->pin = pin;
    pinMode(this->pin, OUTPUT);
}

void RelayController::setParent(App *parent)
{
    parent->runCommand("on");
}

String RelayController::status()
{
    if (digitalRead(this->pin) == HIGH)
        return "on";
    else
        return "off";
}

void RelayController::status(String status)
{
    if (status == "on")
    {
        digitalWrite(this->pin, HIGH);
    }
    else
    {
        digitalWrite(this->pin, LOW);
    }
}
