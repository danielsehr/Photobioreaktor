import { WebSocketClient } from "./web/websocket-client.js";
import { CurrentMeasurements } from "./ui/current-measurements.js";
import { ChartManager } from "./ui/chart-manager.js";

import { SettingsUi } from "./ui/settings-ui.js";
import { ExperimentUi } from "./ui/experiment-ui.js";

import { SettingsManager } from "./manager/settings-manager.js";
import { ExperimentManager } from "./manager/experiment-manager.js";
import { initialize } from "./manager/initialize-manager.js";

import { TimeApi } from "./api/time-api.js";


const socket = new WebSocketClient();
const currentMeasurements = new CurrentMeasurements();
const chartManager = new ChartManager();

const experimentUi = new ExperimentUi();
const settingsUi = new SettingsUi();

const experimentManager = new ExperimentManager(experimentUi);
const settingsManager = new SettingsManager(settingsUi);

const timeApi = new TimeApi();

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


initialize(settingsManager, experimentManager, settingsUi, timeApi);