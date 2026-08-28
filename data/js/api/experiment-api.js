export class ExperimentApi {
    async getStatus() {
        const response = await fetch("/api/experiment/status");

        if (!response.ok) {
            throw new Error(
                `Failed to retrieve experiment status: ${response.status}`
            );
        }

        return response.json();
    }


    async getExperiments() {
        const response = await fetch(
            "/api/experiments"
        );

        if (!response.ok) {
            throw new Error(
                `Failed to load experiments: ${response.status}`
            );
        }

        return response.json();
    }


    async start() {
        const response = await fetch(
            "/api/experiment/start",
            { method: "POST" }
        );

        if (!response.ok) {
            throw new Error(
                `Failed to start experiment: ${response.status}`
            );
        }
    }


    async stop() {
        const response = await fetch(
            "/api/experiment/stop",
            { method: "POST" }
        );

        if (!response.ok) {
            throw new Error(
                `Failed to stop experiment: ${response.status}`
            );
        }
    }


    async download(id) {
        const response = await fetch(
            `/api/experiment/download?id=${id}`
        );

        if (!response.ok) {
            throw new Error(
                `Failed to download experiment: ${response.status}`
            );
        }

        return response.blob();
    }
}