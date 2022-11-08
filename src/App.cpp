#include <Arduino.h>
#include <App.h>
#include <RelayController.h>
#include <sensor_soil.h>
#include <SensorWaterflow.h>
#include <WifiManager.h>

RelayController pumpRelay(14);
SensorWaterflow sensorWaterflow(2);
WifiManager wifiManager;

void App::setup()
{
    Serial.begin(115200);
    Serial.println("starting app");
    wifiManager.init();
    wifiManager.setParent(this);
}

void App::loop()
{
    curMillis = millis();
    sensorWaterflow.loop();
    wifiManager.loop();

    float flow = sensorWaterflow.getFlowRate();
    // int flow = 0; // remover

    // json output =========================================================================
    if (curMillis - prevMillis > pubInterval)
    {
        String json = String("{") + "\"device_id\":\"" + device_id + "\",\"data\":{\"pump_status\":\"" + pumpRelay.status() + "\",\"soil\":" + getSoilHumidity() + ",\"waterflow\":" + flow + "}}";
        Serial.println(json);
        char copy[250];
        json.toCharArray(copy, 250);
        // publish_mqtt(copy);
        prevMillis = curMillis;
    }
}

void App::runCommand(String command)
{
    int pos = command.indexOf("=");
    String key = command.substring(0, pos);
    String value = command.substring(pos + 1);
    Serial.println("==> running command: " + key + ":" + value);
    if (key == "pump_status")
    {
        pumpRelay.status(value);
    }
}

// Replaces placeholder with LED state value
String processor1(const String &var)
{

    Serial.println(var);
    return "oi";
    // return String();
}