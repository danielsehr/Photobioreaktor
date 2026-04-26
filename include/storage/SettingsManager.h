#include <Preferences.h>
#include "core/SystemTypes.h"


class SettingsManager {
    public:
        bool begin();
        bool load(SystemSettings& settings);
        bool save(const SystemSettings& settings);

    private:
        Preferences preferences;
        static constexpr const char* NAMESPACE_NAME = "settings";
};