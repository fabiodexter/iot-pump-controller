#ifndef TESTE_1_H_INCLUDED
#define TESTE_1_H_INCLUDED
#include <Arduino.h>

class App
{
private:
    const char *device_id = "wellpump_controller";
    const char *mqtt_server = "192.168.4.111";
    long curMillis = 0;
    long prevMillis = 0;
    int pubInterval = 1000;

public:
    const char *device_topic = "/controllers/pump_controller/#";
    App()
    {
    }
    void setup();
    void loop();
    void runCommand(String command);
    void processor1(const String &var);
};
#endif // TESTE_1_H_INCLUDED