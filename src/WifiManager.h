#include <Arduino.h>
#include <App.h>

class WifiManager
{
private:
    App *parent;

public:
    WifiManager();
    void setParent(App *_parent);
    void init();
    void loop();
};