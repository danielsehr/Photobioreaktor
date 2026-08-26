export class CurrentMeasurements {
    constructor() {
        this.status = document.getElementById("status");
        this.uptimeSeconds = document.getElementById("espTimeField");
        this.temperature = document.getElementById("tempField");
        this.conductivity = document.getElementById("condField");
        this.turbidity = document.getElementById("turbField");
        this.waterLevel = document.getElementById("levelField");
    }
    
    updateCurrentMeasurement(data){
        this.uptimeSeconds.textContent = `${data.uptimeSeconds.toFixed(1)}`;
        this.temperature.textContent = `${data.temperature.toFixed(1)}`;
        this.conductivity.textContent = `${data.conductivity.toFixed(1)}`;
        this.turbidity.textContent = `${data.turbidity.toFixed(1)}`;
        this.waterLevel.textContent = `${data.waterLevel.toFixed(1)}`;
    }
}