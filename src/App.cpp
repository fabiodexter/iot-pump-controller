#include <Arduino.h>
#include <App.h>
#include <RelayController.h>
#include <sensor_soil.h>
#include <SensorWaterflow.h>
#include <WifiManager.h>
#include <mqtt.h>




RelayController pumpRelay(14);
SensorWaterflow sensorWaterflow(2);
WifiManager wifiManager;
MQTTManager mqtt_manager;

void App::setup()
{
    Serial.begin(115200);
    Serial.println("starting app");
    wifiManager.init();
    wifiManager.setParent(this);
    mqtt_manager.setParent(this);
}



void App::loop()
{
    curMillis = millis();
    sensorWaterflow.loop();
    wifiManager.loop();
    mqtt_manager.loop_mqtt();

    float flow = sensorWaterflow.getFlowRate();
    // int flow = 0; // remover

    // json output =========================================================================
    if (curMillis - prevMillis > pubInterval)
    {
        String json = String("{") + "\"device_id\":\"" + device_id + "\",\"data\":{\"pump_status\":\"" + pumpRelay.status() + "\",\"soil\":" + getSoilHumidity() + ",\"waterflow\":" + flow + "}}";
        Serial.println(json);
        char copy[250];
        json.toCharArray(copy, 250);
        mqtt_manager.publish_mqtt(copy);
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
String App::exposeMetrics(String var)
{
    //Serial.println(var);
    float flow = sensorWaterflow.getFlowRate();
    if(var=="PUMP_STATUS") return pumpRelay.status();
    else if(var=="WATER_FLOW") return String(flow);
    else if(var=="SOIL_HUMIDITY") return String(int(getSoilHumidity()*100));
    return String("N/A");

}