#include <cstddef>

#include "Temperature.h"

Temperature::Temperature(float temp, Temperature::Unit unit)
{
    this->setTemperature(temp, unit);
}

Temperature::Temperature(const Temperature& temp)
{
    this->temperature = temp.temperature;
}

float Temperature::getTemperature() const
{
    return this->getTemperature(Temperature::CurrentUnit);
}

float Temperature::getTemperature(Temperature::Unit unit) const
{
    switch(unit)
    {
        case Temperature::Unit::FARENHEIT:
            return this->temperature * 1.8f + 32.0f;
            break;
        case Temperature::Unit::CELSIUS:
            return this->temperature;
            break;
        default:
            return -100.0f;
    }
}

void Temperature::setTemperature(float temp, Temperature::Unit unit)
{
    if(unit == Temperature::Unit::FARENHEIT)
        this->temperature = (temp - 32.0f) / 1.8f;
    else if (unit == Temperature::Unit::CELSIUS)
        this->temperature = temp;
    
}

bool Temperature::operator==(const Temperature& temp)
{
    return this->temperature == temp.temperature;
}

bool Temperature::operator<(const Temperature& temp)
{
    if(this == NULL)
        return true;
    return this->temperature < temp.temperature;
}

bool Temperature::operator>(const Temperature& temp)
{
    if(this == NULL)
        return false;
    return this->temperature > temp.temperature;
}

Temperature Temperature::operator+(const Temperature& temp)
{
    float ltemp = this->getTemperature(FARENHEIT);
    float rtemp = temp.getTemperature(FARENHEIT);
    return Temperature(ltemp + rtemp, FARENHEIT);
}

Temperature Temperature::operator-(const Temperature& temp)
{
    return Temperature(this->getTemperature(FARENHEIT) - temp.getTemperature(FARENHEIT), FARENHEIT);
}

Temperature& Temperature::operator=(const Temperature& temp)
{
	temperature = temp.temperature;

	return *this;
}