#pragma once

class NetworkManager
{
public:
    void begin();

    const char* getIpAdress() const;

private:
    char ipBuffer[16] = {};
};