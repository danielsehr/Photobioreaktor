#pragma once

#include "state/SensorData.h"


class Logger
{
public:

    static void begin();

    static void info(const char* message);

    static void info(const SensorData& data);

    static void infof(const char* format, ...);


    static void warning(const char* message);


    static void error(const char* message);

    static void errorf(const char* format, ...);
};


#define LOG_INFO(...) Logger::infof(__VA_ARGS__)

#define LOG_WARNING(msg) Logger::warning(msg)

// #define LOG_ERROR(msg) Logger::error(msg)
#define LOG_ERROR(...) Logger::errorf(__VA_ARGS__)
