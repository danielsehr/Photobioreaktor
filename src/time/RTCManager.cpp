#include "time/RTCManager.h"
#include <Arduino.h>


void RTCManager::begin() {
    update();
}

bool RTCManager::setDateTime(const char* dateStr, const char* timeStr) 
{
    int year, month, day;
    int hour, minute, second = 0;

    if(sscanf(dateStr, "%4d-%2d-%2d", &year, &month, &day) != 3)
        return false;
    
    int parsed = sscanf(timeStr, "%2d:%2d:%2d", &hour, &minute, &second);

    if (parsed < 2)
    {
        return false;
    }

    rtc.setTime(second, minute, hour, day, month, year);

    update();

    return true;
}   

void RTCManager::update() 
{
    currentHour = rtc.getHour(true);

    snprintf(
        dateBuffer, sizeof(dateBuffer),
        "%04d-%02d-%02d",
        rtc.getYear(),
        rtc.getMonth() + 1,
        rtc.getDay()
    );

    snprintf(
        timeBuffer, sizeof(timeBuffer),
        "%02d:%02d:%02d",
        rtc.getHour(true),
        rtc.getMinute(),
        rtc.getSecond()
    );
}

const char* RTCManager::getDate() const {
    return dateBuffer;
}

const char* RTCManager::getTime() const {
    return timeBuffer;
}

int RTCManager::getHour() const {
    return currentHour;
}