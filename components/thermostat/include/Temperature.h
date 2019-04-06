#pragma once

class Temperature
{
public:
    
    enum Unit
    {
        FARENHEIT,
        CELSIUS
    };

    const static Unit CurrentUnit = FARENHEIT;

    Temperature(float temp, Unit unit);

    Temperature(const Temperature& temp);

    float getTemperature() const;

    float getTemperature(Unit unit) const;

    void setTemperature(float temp, Unit unit);

    bool operator==(const Temperature& temp);

    bool operator<(const Temperature& temp);

    bool operator>(const Temperature& temp);

    Temperature operator+(const Temperature& temp);

    Temperature operator-(const Temperature& temp);

    Temperature& operator=(const Temperature& temp);
    
    Temperature() { };

private:
    float temperature = 0.0;
};