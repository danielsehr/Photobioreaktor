#include "time/RTCManager.h"
#include <Arduino.h>


void RTCManager::begin() {
    update();
}

bool RTCManager::setDateTime(const char* dateStr, const char* timeStr) 
{
    int year = 0;
    int month = 0;
    int day = 0;

    int hour = 0;
    int minute = 0;
    int second = 0;

    if(sscanf(dateStr, "%4d-%2d-%2d", &year, &month, &day) != 3)
    {
        return false;
    }
    
    const int parsed = sscanf(timeStr, "%2d:%2d:%2d", &hour, &minute, &second);

    if (parsed < 2)
    {
        return false;
    }

    if (
        month < 1 || month > 12 ||
        day < 1 || day > 31 ||
        hour < 0 || hour > 23 ||
        minute < 0 || minute > 59 ||
        second < 0 || second > 59
    )
    {
        return false;
    }
    rtc_.setTime(second, minute, hour, day, month, year);

    update();

    return true;
}   

void RTCManager::update() 
{
    snprintf(
        dateBuffer_, 
        sizeof(dateBuffer_),
        "%04d-%02d-%02d",
        rtc_.getYear(),
        rtc_.getMonth() + 1,
        rtc_.getDay()
    );

    snprintf(
        timeBuffer_, sizeof(timeBuffer_),
        "%02d:%02d:%02d",
        rtc_.getHour(true),
        rtc_.getMinute(),
        rtc_.getSecond()
    );
}

const char* RTCManager::getDate() const {
    return dateBuffer_;
}

const char* RTCManager::getTime() const {
    return timeBuffer_;
}

int RTCManager::getHour()
{
    return rtc_.getHour(true);
}