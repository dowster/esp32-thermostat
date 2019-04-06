#pragma once

#include "Temperature.h"
#include "Relay.h"
#include "TemperatureSensor.h"
#include "Schedule.h"

class Thermostat
{
public:
    enum OperatingModes 
    {
        Heating,
        Cooling,
        Off
    };

    enum TargetSource
    {
        Scheduled,
        Manual
    };

    const int WaitPeriod = 15;
    Temperature Threshold = Temperature(1.5f, Temperature::Unit::FARENHEIT);

    /**
     * Create a new thermostat with the given TemperatureSensor, Heating Relay, and Cooling Relay.
     * 
     * @param temperatureSensor A concrete temperature sensor class
     * @param heatingRelay A concrete implementation of relay used to control heating
     * @param coolingRelay A concrete implementation of relay used to control cooling
     */
    Thermostat(
        TemperatureSensor * temperatureSensor, 
        Relay * heatingRelay,
        Relay * coolingRelay);

    /**
     * Change the operating mode and process transition logic.
     * 
     * @param mode The OperatingMode to transition to
     */
    void setOperatingMode(OperatingModes mode);

    /**
     * Get the current operating mode of the thermostat.
     * 
     * @return the current operating mode
     */
    OperatingModes getOperatingMode();

    /**
     * Change the target source of the thermostat.
     * 
     * The target source is where the thermostat gets it's target temperature.
     * 
     * @param source Anything in TargetSource
     */
    void setSource(TargetSource source);

    /**
     * Get the current target source.
     * 
     * @return 
     */
    TargetSource getSource();

    /**
     * Set the target temperature.
     * 
     * This does not take affect when the target source 
     * is set to Thermostat::TargetSource::Manual.
     * 
     * @param target The desired temperature target.
     */
    void setTarget(const Temperature & target);

    /**
     * Get the target temperature. 
     * 
     * Return a copy of a temperature object.
     */
    Temperature getTarget();

    /**
     * Set the Thermostats schedule to use when TargetSource is set to 
     * Thermostat::TargetSource::Schedule.
     * 
     * Deletes the current schedule object.
     */
    void setSchedule(Schedule * schedule);

    /**
     * Get the reference to the current schedule used by the thermostat. 
     */
    Schedule * getSchedule();

    /**
     * Get the current temperature read in by the Thermostat's temperature
     * sensor.
     */
    Temperature getTemperature();

    /**
     * Process a loop of the thermostat main logic.
     */
    void loop();

    /**
     * Default constructor, don't use it because it won't do you any favors.
     */
    Thermostat() { };

    /**
     * Get the reference to the heating relay used by the thermostat. 
     */
    Relay * getHeatingRelay();

    /**
     * Get the reference to the cooling relay used by the thermostat. 
     */
    Relay * getCoolingRelay();

    /**
     * Get the current value of the internal debounce counter.
     */
    int getDebounce() { return this->debounce; };

private:
   // Thermostat(Thermostat * thermostat) { };

    void runHeat();

    void runOff();

    void runCool();

    OperatingModes operatingMode = Off;
    Temperature target;
    TemperatureSensor * temperatureSensor = 0;
    Relay * heatingRelay;
    Relay * coolingRelay;
    int debounce = 0;
    TargetSource targetSource = Thermostat::TargetSource::Manual;
    Schedule * schedule = 0;
};