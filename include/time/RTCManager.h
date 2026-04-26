#pragma once
#include <ESP32Time.h>


class RTCManager {
    public:
        void begin();

        bool setDateTime(const char* dateStr, const char* timeStr);

        void update();

        // Getters
        const char* getDate() const;
        const char* getTime() const;

        int getHour() const;

    private:
        ESP32Time rtc{0};

        char dateBuffer[11] = {}; // char buffer instead of heap allocating strings
        char timeBuffer[9] = {};

        int currentHour = 0;
};