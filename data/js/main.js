const socket = new WebSocket(`ws://${location.host}/ws`);

socket.onmessage = (event) => {
    const data = JSON.parse(event.data);

    document.getElementById('espTimeField').textContent = data.uptimeSeconds ?? '--';
    document.getElementById('tempField').textContent = data.temperature ?? '--';
    document.getElementById('condField').textContent = data.conductivity ?? '--';
    document.getElementById('turbField').textContent = data.turbidity ?? '--';
    document.getElementById('levelField').textContent = data.waterLevel ?? '--';
};