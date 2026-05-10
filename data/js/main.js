async function fetchSensorData() {
    try {
        const res = await fetch('/data.json', { cache: "no-store" });
        if (!res.ok) return;

        const data = await res.json();

        document.getElementById('espTimeField').textContent = data.uptimeSeconds ?? '--';
        document.getElementById('tempField').textContent = data.temperature ?? '--';
        document.getElementById('condField').textContent = data.conductivity ?? '--';
        document.getElementById('turbField').textContent = data.turbidity ?? '--';
        document.getElementById('levelField').textContent = data.waterLevel ?? '--';

    } catch (err) {
        console.error('Sensor fetch failed:', err);
    }
}

function startSensorPolling(intervalMs = 2000) {
    fetchSensorData();
    setInterval(fetchSensorData, intervalMs);
}

// auto-start when script loads
startSensorPolling();