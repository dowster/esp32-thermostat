//extern "C"{
//#include "mgos.h"
//}

#include <cstddef>

#include "Thermostat.h"
#include "Temperature.h"
#include "Schedule.h"

Thermostat::Thermostat(
    TemperatureSensor * temperatureSensor,
    Relay * heatingRelay, 
    Relay * coolingRelay)
{
    this->temperatureSensor = temperatureSensor;

    this->heatingRelay = heatingRelay;
    this->coolingRelay = coolingRelay;
}

void Thermostat::setOperatingMode(OperatingModes mode)
{
    if(this->operatingMode != mode)
        this->runOff();

    this->operatingMode = mode;
}

Thermostat::OperatingModes Thermostat::getOperatingMode()
{
    return this->operatingMode;
}

void Thermostat::setTarget(const Temperature & target)
{
    this->target = target;
}

Temperature Thermostat::getTarget()
{
    if(this->targetSource == Thermostat::TargetSource::Scheduled)
        return this->schedule->getTarget(0, 1.0f);
    return this->target;
}

void Thermostat::setSource(TargetSource source)
{
    this->targetSource = source;
}

Thermostat::TargetSource Thermostat::getSource()
{
    return this->targetSource;
}

void Thermostat::setSchedule(Schedule * schedule)
{
    delete this->schedule;

    this->schedule = schedule;
}

Schedule * Thermostat::getSchedule()
{
    return this->schedule;
}

Temperature Thermostat::getTemperature()
{
    return this->temperatureSensor->getTemperature();
}

void Thermostat::loop()
{
    switch(this->operatingMode)
    {
        case Heating:
            this->runHeat();
            break;
        case Cooling: 
            this->runCool();
            break;
        case Off:
            this->runOff();
            break;
    }
}

void Thermostat::runHeat()
{
        Temperature currentTemp = this->temperatureSensor->getTemperature();

        if(
            !this->heatingRelay->isOn() &&
            currentTemp < this->getTarget() - this->Threshold 
        )
        {
            if(++this->debounce >= this->WaitPeriod)
            {
                this->heatingRelay->turnOn();
                this->debounce = 0;
            }
        }
        else if(
            this->heatingRelay->isOn() &&
            currentTemp > this->getTarget() + this->Threshold
        )
        {
            if(++this->debounce >= this->WaitPeriod)
            {
                this->heatingRelay->turnOff();
                this->debounce = 0;
            }
        }
        else
        {
            this->debounce = 0;
        }
    
}

void Thermostat::runCool()
{
        Temperature currentTemp = this->temperatureSensor->getTemperature();

        if(
            !this->coolingRelay->isOn() &&
            currentTemp > this->getTarget() + this->Threshold
        )
        {
            if(++this->debounce >= this->WaitPeriod)
            {
                this->coolingRelay->turnOn();
                this->debounce = 0;
            }
        }
        else if(
            this->coolingRelay->isOn() &&
            currentTemp < this->getTarget() - this->Threshold
        )
        {
            if(++this->debounce >= this->WaitPeriod)
            {
                this->coolingRelay->turnOff();
                this->debounce = 0;
            }
        }
        else
        {
            this->debounce = 0;
        }
    
}

void Thermostat::runOff()
{
    if(this->heatingRelay->isOn())
        this->heatingRelay->turnOff();
    if(this->coolingRelay->isOn())
        this->coolingRelay->turnOff();
    if(this->debounce != 0)
        this->debounce = 0;
}

Relay * Thermostat::getHeatingRelay() {
    return this->heatingRelay;
}

Relay * Thermostat::getCoolingRelay() {
    return this->coolingRelay;
}