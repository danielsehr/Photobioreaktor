export async function initialize(
    settingsManager,
    experimentManager,
    settingsUi,
    timeApi
) {
    try {
        await timeApi.synchronize();
    }
    catch (error) {
        console.error(
            "[Initialize Manager] Failed to synchronize time:",
            error
        );
    }


    try {
        const settings =
            await settingsManager.load();

        settingsUi.displaySettings(settings);
    }
    catch (error) {
        console.error(
            "[Initialize Manager] Failed to load settings:",
            error
        );

        alert(
            "Fehler beim Laden der Einstellungen."
        );
    }


    settingsUi.onSave(async () => {
        try {
            const settings =
                settingsUi.getSettings();

            await settingsManager.update(settings);

            alert(
                "Einstellungen gespeichert."
            );
        }
        catch (error) {
            console.error(
                "[Initialize Manager] Failed to save settings:",
                error
            );

            alert(
                "Fehler beim Speichern der Einstellungen."
            );
        }
    });


    await experimentManager.initialize();
}