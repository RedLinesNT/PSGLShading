#pragma once

#include <ctime>

class DeltaTime {
public:
    inline DeltaTime() { lastTime = std::clock(); }

    inline float GetDeltaTime() {
        std::clock_t currentTime = std::clock();
        float deltaTime = ((float)(currentTime - lastTime) / (CLOCKS_PER_SEC / 1000)); //MS instead of SECS

        lastTime = currentTime;
        
        return deltaTime;
    }

private:
    std::clock_t lastTime;
};