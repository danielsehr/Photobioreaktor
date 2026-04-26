// #pragma once // still not sure if we need this
#include <Arduino.h>

// --- Pin mapping ---
namespace Config{
    // --- Relay ---
    constexpr gpio_num_t PIN_HEATER = GPIO_NUM_14;
    constexpr gpio_num_t PIN_STIRRER = GPIO_NUM_13;
    constexpr gpio_num_t PIN_LIGHT = GPIO_NUM_12;
    
    constexpr gpio_num_t PIN_STATUS_LED = GPIO_NUM_33;

    constexpr gpio_num_t PIN_ONEWIRE      = GPIO_NUM_32;
    constexpr gpio_num_t PIN_TDS          = GPIO_NUM_35;
    constexpr gpio_num_t PIN_TURBIDITY    = GPIO_NUM_34;

    constexpr gpio_num_t PIN_TRIG         = GPIO_NUM_25;
    constexpr gpio_num_t PIN_ECHO         = GPIO_NUM_27;

    constexpr gpio_num_t PIN_RESET        = GPIO_NUM_26;


    // --- ADC ---
    constexpr float ADC_REFERENCE_VOLTAGE = 3.3f;
    constexpr uint16_t ADC_RESOLUTION     = 4095;

    // --- Files ---
    constexpr const char* DATA_FILE = "/data.csv";

    // --- WiFi---
    constexpr const char* AP_SSID = "Photobioreaktor";
    constexpr const char* AP_PASSWORD = "123456789";
}
