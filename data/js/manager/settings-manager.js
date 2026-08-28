import { SettingsApi } from "../api/settings-api.js";

export class SettingsManager {
    constructor() {
        this.api = new SettingsApi();
        this.settings = null;
    }

    async load() {
        this.settings = await this.api.getSettings();

        return this.settings;
    }

    async update(settings) {
        this.settings = await this.api.updateSettings(settings);

        return this.settings;
    }

    getSettings() {
        return this.settings;
    }
}