#pragma once
#include "Core/DebugConsole.h"

class StatsConsole final : public DebugConsole {
public:
    StatsConsole(const DebugConsoleInitOptions& options);
    virtual ~StatsConsole() = default;

    static StatsConsole* Create();
protected:
    void Update(float deltaTime) override;
};
