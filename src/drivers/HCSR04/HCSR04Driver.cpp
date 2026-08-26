# include "HCSR04Driver.h"

namespace
    {
    constexpr float EMPTY_DISTANCE_CM = 19.0f;
    constexpr float SAFE_DISTANCE_CM = 5.0f;

    constexpr unsigned long ECHO_TIMEOUT_US = 2600;
    constexpr float DISTANCE_CONVERSION_FACTOR = 58.2f;
    }

int HCSR04Driver::readWaterLevel()
{
    digitalWrite(Config::PIN_TRIG, LOW);
    delayMicroseconds(2);

    digitalWrite(Config::PIN_TRIG, HIGH);
    delayMicroseconds(10);

    digitalWrite(Config::PIN_TRIG, LOW);

    const unsigned long duration =
        pulseIn(Config::PIN_ECHO, HIGH, ECHO_TIMEOUT_US);
    
    if (duration == 0)
    {
        return 0;
    }

    const float distance =
        duration / DISTANCE_CONVERSION_FACTOR;

    int level = static_cast<int>(
        (EMPTY_DISTANCE_CM - distance) /
        (EMPTY_DISTANCE_CM - SAFE_DISTANCE_CM) * 100.0f
    );


    if (level < 0)
        level = 0;

    if (level > 100)
        level = 100;

    return level;
}