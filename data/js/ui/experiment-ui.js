export class ExperimentUi {
    constructor() {
        this.startButton = document.getElementById("startExperiment");
        this.stopButton = document.getElementById("stopExperiment");
        this.downloadButton = document.getElementById("downloadCsv");
        this.selectExperiment = document.getElementById("selectExperiment");
        this.experimentStatus = document.getElementById("experimentStatus")
    }

    setRecording(recording) {
        this.startButton.disabled = recording;
        this.stopButton.disabled = !recording;

        this.experimentStatus.textContent =
            recording
                ? "Recording"
                : "Not recording";
    }

    getSelectedExperimentId(){
        return this.selectExperiment.value
    }

    setExperiments(experiments) {
        const selectedId = selectExperiment.value;

        this.selectExperiment.replaceChildren();

        for (const experiment of experiments)
        {
            const option =
                document.createElement("option");

            option.value = experiment.id;
            option.textContent =
                `Experiment ${experiment.id}`;

            this.selectExperiment.appendChild(option);
        }

        if (selectedId !== "")
        {
            this.selectExperiment.value = selectedId;
        }
    }
    
    onStartClicked(callback){
        this.startButton.addEventListener("click", callback);
    }

    onStopClicked(callback)
    {
        this.stopButton.addEventListener("click", callback);
    }

    onDownloadClicked(callback)
    {
        this.downloadButton.addEventListener("click", callback);
    }

}