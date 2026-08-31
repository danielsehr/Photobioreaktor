export class ChartManager {
    static BUFFER_SIZE = 864;

    constructor() {
        this.ctx =
            document
                .getElementById("chart")
                .getContext("2d");

        this.chart = new Chart(this.ctx, {
            type: "line",

            data: {
                labels: [],
                datasets: [
                    {
                        label: "Temperatur",
                        data: [],
                        yAxisID: "temperature",

                        borderColor: "#e53935",
                        backgroundColor: "#e53935",
                    },
                    {
                        label: "Leitfähigkeit",
                        data: [],
                        yAxisID: "conductivity",

                        borderColor: "#2A9D8F",
                        backgroundColor: "#2A9D8F",
                    },
                    {
                        label: "Trübung",
                        data: [],
                        yAxisID: "turbidity",

                        borderColor: "#C99A00",
                        backgroundColor: "#C99A00",
                    },
                    {
                        label: "Füllvolumen",
                        data: [],
                        yAxisID: "waterLevel",

                        borderColor: "#457B9D",
                        backgroundColor: "#457B9D",
                    }
                ]
            },

            options: {
                animation: false,
                responsive: true,

                scales: {
                    temperature: {
                        type: "linear",
                        position: "left",
                        min: 0,
                        max: 50,
                        display: true,

                        ticks: {
                            color: "#e53935",
                        },
                    },

                    conductivity: {
                        type: "linear",
                        position: "right",
                        min: 0,
                        max: 2000,
                        display: true,
                        ticks: {
                            color: "#2A9D8F",
                        },
                    },

                    turbidity: {
                        type: "linear",
                        position: "right",
                        min: 0,
                        max: 1000,
                        display: true,
                        ticks: {
                            color: "#C99A00",
                        },
                    },

                    waterLevel: {
                        type: "linear",
                        position: "left",
                        min: 0,
                        max: 100,
                        display: true,
                        grid: {
                            drawOnChartArea: false,
                        },

                    ticks: {
                            color: "#457B9D",
                        },
                    },
                }
            }
        });
    }


    #createTimestamp() {
        return new Date().toLocaleTimeString();
    }

    #appendMeasurement(data) {
        this.chart.data.labels.push(this.#createTimestamp());
        this.chart.data.datasets[0].data.push(data.temperature);
        this.chart.data.datasets[1].data.push(data.conductivity);
        this.chart.data.datasets[2].data.push(data.turbidity);
        this.chart.data.datasets[3].data.push(data.waterLevel);
    }

    #trimBuffer() {
        if (this.chart.data.labels.length > ChartManager.BUFFER_SIZE) {
            this.chart.data.labels.shift();

            this.chart.data.datasets[0].data.shift();
            this.chart.data.datasets[1].data.shift();
            this.chart.data.datasets[2].data.shift();
            this.chart.data.datasets[3].data.shift();
        }
    }

    addMeasurement(data) {
        this.#appendMeasurement(data);
        this.#trimBuffer();
        this.chart.update();
    }
}