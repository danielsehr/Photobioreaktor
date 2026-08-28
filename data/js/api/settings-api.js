export class SettingsApi {
    async getSettings() {
        const response = await fetch("/api/settings");

        if (!response.ok) {
            throw new Error(
                `Failed to retrieve settings: ${response.status}`
            );
        }

        return response.json();
    }

    async updateSettings(settings) {
        const response = await fetch("/api/settings", {
            method: "PUT",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify(settings)
        }
        );

        if (!response.ok) {
            throw new Error(
                `Failed to update settings: ${response.status}`
            );
        }

        return response.json();
    }
}