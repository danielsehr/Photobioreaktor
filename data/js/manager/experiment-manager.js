import { ExperimentApi } from "../api/experiment-api.js";

export class ExperimentManager {
    constructor(ui) {
        this.ui = ui;
        this.api = new ExperimentApi();

        this.initializeEventListeners();
    }


    async initialize() {
        await this.initializeState();
        await this.loadExperiments();
    }


    initializeEventListeners() {
        this.ui.onStartClicked(
            () => this.start()
        );

        this.ui.onStopClicked(
            () => this.stop()
        );

        this.ui.onDownloadClicked(
            () => this.download()
        );
    }


    async start() {
        try {
            await this.api.start();

            this.ui.setRecording(true);

            await this.loadExperiments();
        }
        catch (error) {
            console.error(error);
        }
    }


    async stop() {
        try {
            await this.api.stop();

            this.ui.setRecording(false);

            await this.loadExperiments();
        }
        catch (error) {
            console.error(error);
        }
    }


    async initializeState() {
        try {
            const state =
                await this.api.getStatus();

            this.ui.setRecording(
                state.recording
            );
        }
        catch (error) {
            console.error(error);
        }
    }


    async loadExperiments() {
        try {
            const experiments =
                await this.api.getExperiments();

            this.ui.setExperiments(
                experiments
            );
        }
        catch (error) {
            console.error(error);
        }
    }


    async download() {
        const id =
            this.ui.getSelectedExperimentId();

        if (!id) {
            return;
        }

        try {
            const blob =
                await this.api.download(id);

            const url =
                URL.createObjectURL(blob);

            const link =
                document.createElement("a");

            link.href = url;
            link.download = `experiment_${id}.csv`;

            document.body.appendChild(link);
            link.click();
            link.remove();

            URL.revokeObjectURL(url);
        }
        catch (error) {
            console.error(error);
        }
    }
}