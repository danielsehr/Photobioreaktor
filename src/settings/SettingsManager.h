#pragma once
#include <Preferences.h>
#include "core/SystemTypes.h"


class SettingsManager {
    public:
        bool begin();
        bool load();
        bool save(const SystemSettings& settings);
        bool reset();

        const SystemSettings& getSettings() const;

    private:
        Preferences preferences;

        SystemSettings settings;
};