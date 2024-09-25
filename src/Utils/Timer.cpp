#include "Timer.h"

Timer::Timer()
{}

Timer::Timer(uint32_t ms_period)
{
    start(ms_period);
}

void Timer::start(uint32_t ms_period) 
{
    _period = ms_period;
    start();
}

void Timer::start() 
{
    _timer = millis();
    if (!_timer) 
        _timer = 1;
}

void Timer::stop() 
{
    _timer = 0;
}

bool Timer::ready() 
{
    if (_timer && millis() - _timer >= _period)
    {
        start();
        return true;
    }
    return false;
}
