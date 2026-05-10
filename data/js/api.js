export async function loadSettings()
{
    const response = await fetch("/settings.json");

    if (!response.ok){
        throw new Error("Failed to fetch settings");
        return null;
    }

    return response.json();
}

window.api = {loadSettings};