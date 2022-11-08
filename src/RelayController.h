#include <Arduino.h>
#include <App.h>

class RelayController
{
private:
    int pin;

public:
    RelayController();
    RelayController(int pin);
    String status();
    void status(String status);
    void setParent(App *parent);
};