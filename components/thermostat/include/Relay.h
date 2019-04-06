#pragma once

class Relay
{
public:    
    Relay() { };

    virtual void turnOn() = 0;

    virtual void turnOff() = 0;

    bool isOn();

protected:
    bool on = false;
};