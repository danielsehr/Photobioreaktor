export class WebSocketClient {
    constructor() {
        this.socket = new WebSocket(`ws://${location.host}/ws`);
    }

    onopen(callback) {
        this.socket.onopen = callback;
    }

    onclose(callback) {
        this.socket.onclose = callback;
    }

    onMeasurement(callback) {
        this.socket.onmessage = (event) => {
            const message = JSON.parse(event.data);

            if (message.type === "sensor") {
                callback(message.data);
            }
        };
    }
}