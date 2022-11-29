#ifndef TESTE_1_H_INCLUDED
#define TESTE_1_H_INCLUDED
#include <Arduino.h>

class App
{
private:
    const char *device_id = "wellpump_controller";
    long curMillis = 0;
    long prevMillis = 0;
    int pubInterval = 1000;

public:
    App()
    {
    }
    void setup();
    void loop();
    void runCommand(String command);
    String exposeMetrics(String var);
};
#endif // TESTE_1_H_INCLUDED