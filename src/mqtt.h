#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <RelayController.h>

WiFiClient espClient;
PubSubClient mqtt_client(espClient);

int tries = 0;
const int maxtries = 5;
int mqtt_connect_millis = 0;

void reconnect()
{
    while (!mqtt_client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        if (mqtt_client.connect(device_id, "renato", "$tr0nz0"))
        {
            Serial.println("connected");
            Serial.println(mqtt_client.subscribe(device_topic));
            Serial.println("subscribed to " + String(device_topic));
        }
        else
        {
            tries = tries + 1;
            if (tries > maxtries)
                return;
            Serial.print("failed, rc=");
            Serial.print(mqtt_client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void subscribe_callback(char *topic, byte *payload, unsigned int length)
{

    payload[length] = '\0';

    String strTopic = (String)topic;
    Serial.println("topic:" + strTopic);

    String strPayload = String((char *)payload); // convert to string
    Serial.println("mqtt command received:" + strPayload);
    RelayController::status(strPayload);
}

void setup_mqtt()
{
    mqtt_client.setServer(mqtt_server, 1883);
    mqtt_client.setCallback(subscribe_callback);
}

void loop_mqtt()
{
    if (!mqtt_client.connected())
    {
        reconnect();
    }
    mqtt_client.loop();
}

void publish_mqtt(char *copy)
{
    if (mqtt_client.connected())
    {
        mqtt_client.publish("/sensors", copy);
    }
}