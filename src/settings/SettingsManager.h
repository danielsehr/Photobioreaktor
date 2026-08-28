#pragma once
#include <Preferences.h>
#include "core/SystemSettings.h"

class SettingsManager {
    public:
        bool begin();

        bool load();

        bool update(const SystemSettings& settings);

        bool reset();

        const SystemSettings& getSettings() const;

    private:
        Preferences preferences_;

        SystemSettings settings_;
};