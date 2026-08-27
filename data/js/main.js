import { WebSocketClient } from "./web/websocket-client.js";
import { CurrentMeasurements } from "./ui/current-measurements.js";
import { ChartManager } from "./ui/chart-manager.js";
import { ExperimentUi } from "./ui/experiment-ui.js";
import { ExperimentManager } from "./experiment/experiment-manager.js";

const socket = new WebSocketClient();
const currentMeasurements = new CurrentMeasurements();
const chartManager = new ChartManager();
const experimentUi = new ExperimentUi();
const experimentManager = new ExperimentManager(experimentUi);

const connectionStatus = document.getElementById("connectionStatus")


socket.onopen(() => {
    connectionStatus.textContent = "Connected";
    connectionStatus.classList.add("connected")
});


socket.onclose(() => {
    connectionStatus.textContent = "Disconnected";
    connectionStatus.classList.remove("connected")
});


socket.onMeasurement((measurement) => {
    currentMeasurements.updateCurrentMeasurement(measurement);

    chartManager.addMeasurement(measurement);
});

experimentManager.initialize()