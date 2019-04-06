#pragma once

#include "Temperature.h"

class TemperatureSensor
{
public:
    virtual Temperature getTemperature() = 0;

};