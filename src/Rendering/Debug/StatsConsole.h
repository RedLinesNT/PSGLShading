#pragma once
#include "Core/DebugConsole.h"

class StatsConsole final : public DebugConsole {
public:
    StatsConsole(const DebugConsoleInitOptions& options);
    virtual ~StatsConsole() = default;

    // ---------------------------------------------------------------------------
    // Create a "StatsConsole" with default settings.
    // ---------------------------------------------------------------------------
    static StatsConsole* Create();
protected:
    void Update(float deltaTime) override;

private:
    // ---------------------------------------------------------------------------
    // The current/latest framerate value displayed by this DebugConsole.
    // ---------------------------------------------------------------------------
    float framerate;

    // ---------------------------------------------------------------------------
    // The time elapsed between the previous and next update of each value
    // displayed by this DebugConsole.
    // ---------------------------------------------------------------------------
    float updateTimeElapsed;
    // ---------------------------------------------------------------------------
    // The interval (in seconds) at which the values of this DebugConsole
    // will be updated.
    // ---------------------------------------------------------------------------
    // Remarks:
    //      Time in seconds!
    // ---------------------------------------------------------------------------
    float updateTimeInterval;
    
};
