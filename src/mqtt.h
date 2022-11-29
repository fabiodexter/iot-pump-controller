#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>
#include <App.h>

class MQTTManager
{
private:
    int tries = 0;
    const int maxtries = 5;
    int mqtt_connect_millis = 0;
    App *parent;

public:
    MQTTManager();
    void reconnect();
    void loop_mqtt();
    void publish_mqtt(char *copy);
    void setParent(App *parent);
};