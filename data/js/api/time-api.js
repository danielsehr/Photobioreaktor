export class TimeApi {
    async synchronize() {
        const { date, time } =
            getLocalDateTime();

        const response = await fetch("/api/time", {
            method: "PUT",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify({
                date,
                time
            })
        });

        if (!response.ok) {
            throw new Error(
                `Failed to synchronize time: ${response.status}`
            );
        }
    }
}


function getLocalDateTime() {
    const now = new Date();

    const date =
        `${now.getFullYear()}-` +
        `${String(now.getMonth() + 1).padStart(2, "0")}-` +
        `${String(now.getDate()).padStart(2, "0")}`;

    const time =
        `${String(now.getHours()).padStart(2, "0")}:` +
        `${String(now.getMinutes()).padStart(2, "0")}:` +
        `${String(now.getSeconds()).padStart(2, "0")}`;

    return { date, time };
}