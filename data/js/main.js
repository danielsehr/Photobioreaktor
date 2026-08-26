import { CurrentMeasurements } from "./ui/current-measurements.js";
import { WebSocketClient } from "./web/websocket-client.js";

const currentMeasurements = new CurrentMeasurements();
const socket = new WebSocketClient();

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

    // chartManager.addMeasurement(measurement);
});