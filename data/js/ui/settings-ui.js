export class SettingsUi {
    constructor() {
        this.maximalTemperatureCelcius =
            document.getElementById("maxTemperatureField");

        this.minTemperatureCelsius =
            document.getElementById("minTemperatureField");

        this.stirringInterval =
            document.getElementById("stirIntervalField");

        this.stirringDuration =
            document.getElementById("stirDurationField");

        this.lightOn =
            document.getElementById("lightOnField");

        this.lightOff =
            document.getElementById("lightOffField");

        this.measurementInterval =
            document.getElementById("measurementIntervalField");

        this.saveButton =
            document.getElementById("saveButton");
    }

    displaySettings(settings) {
        this.maximalTemperatureCelcius.value =
            settings.maximalTemperatureCelcius;

        this.minTemperatureCelsius.value =
            settings.minimalTemperatureCelcius;

        this.stirringInterval.value =
            settings.stirringIntervalMinutes;

        this.stirringDuration.value =
            settings.stirringDurationMinutes;

        this.lightOn.value =
            settings.lightOnHour;

        this.lightOff.value =
            settings.lightOffHour;

        this.measurementInterval.value =
            settings.measurementIntervalSeconds;
    }

    getSettings() {
        return {
            maximalTemperatureCelcius:
                Number(this.maximalTemperatureCelcius.value),

            minTemperatureCelsius:
                Number(this.minTemperatureCelsius.value),

            stirringIntervalMinutes:
                Number(this.stirringInterval.value),

            stirringDurationMinutes:
                Number(this.stirringDuration.value),

            lightOnHour:
                Number(this.lightOn.value),

            lightOffHour:
                Number(this.lightOff.value),

            measurementIntervalSeconds:
                Number(this.measurementInterval.value)
        };
    }

    onSave(callback) {
        this.saveButton.addEventListener(
            "click",
            callback
        );
    }
}