#pragma once
#include <ESP32Time.h>


class RTCManager {
    public:
        void begin();

        bool setDateTime(const char* dateStr, const char* timeStr);

        void update();

        const char* getDate() const;
        
        const char* getTime() const;

        int getHour();

    private:
        ESP32Time rtc_{0};

        char dateBuffer_[11] = {};
        
        char timeBuffer_[9] = {};
};