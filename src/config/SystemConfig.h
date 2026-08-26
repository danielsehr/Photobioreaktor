#pragma once // still not sure if we need this
#include <Arduino.h>

// --- Pin mapping ---
namespace Config{
    // --- Relay ---
    constexpr gpio_num_t PIN_HEATER       = GPIO_NUM_14;
    constexpr gpio_num_t PIN_STIRRER      = GPIO_NUM_13;
    constexpr gpio_num_t PIN_LIGHT        = GPIO_NUM_12;
    
    constexpr gpio_num_t PIN_STATUS_LED   = GPIO_NUM_33;

    constexpr gpio_num_t PIN_ONEWIRE      = GPIO_NUM_32;
    constexpr gpio_num_t PIN_TDS          = GPIO_NUM_35;
    constexpr gpio_num_t PIN_TURBIDITY    = GPIO_NUM_34;

    constexpr gpio_num_t PIN_TRIG         = GPIO_NUM_25;
    constexpr gpio_num_t PIN_ECHO         = GPIO_NUM_27;

    constexpr gpio_num_t PIN_RESET        = GPIO_NUM_26;


    // SensorService
    constexpr uint32_t SENSOR_UPDATE_MS = 5000U;

    // StorageManager
    constexpr const std::size_t CSV_PATH_MAX = 32;

    // --- Files ---
    constexpr const char* DATA_FILE = "/data.csv";
    constexpr const char* HISTORY_FILE_TEMPLATE = "/experiments/exp%03lu.csv";

    // --- WiFi---
    constexpr const char* AP_SSID = "Photobioreaktor";
    constexpr const char* AP_PASSWORD = "123456789";
}
