#include <Arduino.h>
#include <memory>

#include "Common/DeviceInterface/DeviceInterfaceController.h"
#include "Screen/Screen.h"
#include "Sensors/Sensors.h"
#include "ControlDevices/ControlDevices.h"
#include "Common/Data.h"


/// ===== globals ===== //

Data& data = Data::GetInstance();

// ===== functions ===== //

void setup(void)
{
    Serial.begin(115200);
    Serial.println(F("=== Start program! ==="));

    // Device interface controller
    std::shared_ptr<DeviceInterfaceController> _deviceInterfaceController = std::make_shared<DeviceInterfaceController>();
    data.SetDeviceController(_deviceInterfaceController);

    // Screen
    Wire.begin(SDA, SCL);
    Serial.println(F("Initialize Screen ..."));
    std::shared_ptr<Screen> _screen = std::make_shared<Screen>();
    data.SetScreen(_screen);
    data.GetDeviceController()->AddDevice(_screen);
    if (!data.GetScreen()->Init())
    {
        Serial.println(F("Error: Display initialization failed"));
        return;
    }
    data.GetScreen()->PrintInitializeScreen();
    Serial.println(F("Screen initialized!"));
    //

    // Sensors
    Serial.println(F("Initialize Sensors ..."));
    std::shared_ptr<Sensors> _sensors = std::make_shared<Sensors>();
    data.SetSensors(_sensors);
    data.GetDeviceController()->AddDevice(_sensors);
    Serial.println(F("Sensors initialized!"));
    //

    // Control devices
    Serial.println(F("Initialize ControlDevices ..."));
    std::shared_ptr<ControlDevices> _controlDevices = std::make_shared<ControlDevices>();
    data.SetControlDevices(_controlDevices);
    data.GetDeviceController()->AddDevice(_controlDevices);
    Serial.println(F("ControlDevices initialized!"));
    //

    delay(3000);
    Serial.println(F("Start menu ..."));
    data.GetDeviceController()->StartTimers();
}

void loop(void)
{
    data.GetDeviceController()->MakeLoopIterations();
}