#pragma once

#include "Temperature.h"
#include <array>

typedef std::array<float, 28> ScheduleData;

class Schedule
{
public:
    Schedule(ScheduleData &schedule) {
        this->setSchedule(schedule);
    };

    Temperature getTarget(int dayOfWeek, float time) {
        //LOG(LL_INFO, ("Getting target for day: %d, time: %f", dayOfWeek, time));

        if(time < 4.0f)
            return Temperature(this->schedule[dayOfWeek * this->daySettings + NIGHT], this->currentUnit);
        else if (time < 8.0f)
            return Temperature(this->schedule[dayOfWeek * this->daySettings + MORNING], this->currentUnit);
        else if(time < 14.0f)
            return Temperature(this->schedule[dayOfWeek * this->daySettings + DAYTIME], this->currentUnit);
        else if(time < 20.0f)
            return Temperature(this->schedule[dayOfWeek * this->daySettings + EVENING], this->currentUnit);
        else
            return Temperature(this->schedule[dayOfWeek * this->daySettings + NIGHT], this->currentUnit);
    };

    void setSchedule(ScheduleData &schedule) {
        this->schedule = schedule;
    };
private:
    enum Temperature::Unit currentUnit = Temperature::Unit::FARENHEIT;

    const int daySettings = 4;

    enum TimeOfDay {
        MORNING = 0,
        DAYTIME = 1,
        EVENING = 2,
        NIGHT = 3
    };

    ScheduleData schedule;
};