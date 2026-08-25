# include "Logger.h"

#include <cstdarg>
#include <cstdio>
# include <Arduino.h>


namespace
{
    constexpr std::size_t LOG_BUFFER_SIZE = 128;

    void formatMessage(
        char* buffer,
        std::size_t bufferSize,
        const char* format,
        va_list args)
    {
        vsnprintf(
            buffer,
            bufferSize,
            format,
            args
        );
    }
}


void Logger::begin()
{
    Serial.begin(115200);
}


void Logger::info(const char* message)
{
    Serial.print("[INFO] ");
    Serial.println(message);
}


void Logger::info(const SensorData& data)
{
    char buffer[LOG_BUFFER_SIZE];

    snprintf(
        buffer,
        sizeof(buffer),
        "Timestamp: %d\n"
        "Temperature: %.1f °C\n"
        "Humidity: %.1f%%\n"
        "Valid: %s",
        data.timestamp,
        data.temperatureCelcius,
        data.humidityPercent,
        data.valid ? "true" : "false"
    );

    info(buffer);
}


void Logger::infof(const char* format, ...)
{
    char buffer[LOG_BUFFER_SIZE];

    va_list args;
    va_start(args, format);

    formatMessage(
        buffer,
        sizeof(buffer),
        format,
        args
    );

    va_end(args);

    info(buffer);
}


void Logger::warning(const char* message)
{
    Serial.print("[WARNING] ");
    Serial.println(message);
}


void Logger::error(const char* message)
{
    Serial.print("[ERROR] ");
    Serial.println(message);
}

void Logger::errorf(const char* format, ...)
{
    char buffer[LOG_BUFFER_SIZE];

    va_list args;
    va_start(args, format);

    formatMessage(
        buffer,
        sizeof(buffer),
        format,
        args
    );

    va_end(args);

    error(buffer);
}