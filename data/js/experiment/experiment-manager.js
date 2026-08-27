export class ExperimentManager {
    constructor(ui) {
        this.ui = ui;

        this.initializeEventListeners();
    }


    async initialize() {
        await this.initializeState();
        await this.loadExperiments();
    }


    initializeEventListeners() {
        this.ui.onStartClicked(
            () => this.start()
        )

        this.ui.onStopClicked(
            () => this.stop()
        )
        
        this.ui.onDownloadClicked(
            () => this.download()
        )
    }


    async start() {
        const response = await fetch("/api/experiment/start", { method: "POST" })

        if (!response.ok) {
            console.error("Failed to start experiment");
            return;
        }

        this.ui.setRecording(true)
        await this.loadExperiments();
    }


    async stop() {
        const response = await fetch("/api/experiment/stop", { method: "POST" })

        if (!response.ok) {
            console.error("Failed to stop experiment");
            return;
        }

        this.ui.setRecording(false);
        await this.loadExperiments();
    }


    async initializeState() {
        const response = await fetch("/api/experiment/status");

        if (!response.ok) {
            console.error(
                "Failed to retrieve experiment status."
            );
            return;
        }

        const state = await response.json();

        this.ui.setRecording(state.recording); //FROM WHERE COMES .recording??
    }


    async loadExperiments(){
        const response = await fetch("/api/experiments");

        if (!response.ok) {
            console.error("Failed to load experiments.");
            return;
        }

        const experiments = await response.json()

        this.ui.setExperiments(experiments);
    }


    async download() {
        const id = this.ui.getSelectedExperimentId()

        if (!id) {
            return;
        }

        const response = await fetch(`/api/experiment/download?id=${id}`);

        if (!response.ok) {
            console.log("Failed to download experiment.");
            return;
        }

        const blob = await response.blob()
        
        const url = URL.createObjectURL(blob);

        const link = document.createElement("a");

        link.href = url;
        link.download = `experiment_${id}.csv`;

        document.body.appendChild(link);
        link.click();
        link.remove();

        URL.revokeObjectURL(url);
    }
}