#include <Arduino.h>
#include <App.h>

class WifiManager
{
private:

public:
    App *parent;
    WifiManager();
    void setParent(App *parent);
    void init();
    void loop();
};