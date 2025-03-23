#include "DeviceInterfaceController.h"

void DeviceInterfaceController::AddDevice(std::shared_ptr<DeviceInterface> device)
{
    _devices.push_back(device);
}

void DeviceInterfaceController::MakeLoopIterations()
{
    for (auto& device : _devices)
    {
        device->LoopIteration();
    }
}

void DeviceInterfaceController::StartTimers()
{
    static bool isStarted = false;
    if (isStarted)
        return;

    for (const auto& device : _devices)
    {
        device->StartTimers();
    }
    isStarted = true;
}
