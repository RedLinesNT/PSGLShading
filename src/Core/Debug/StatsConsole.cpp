#include "StatsConsole.h"

StatsConsole* StatsConsole::Create() {
    DebugConsoleInitOptions options;
    options.Name = "StatsConsole";
    options.PositionLeft = 0.0f;
    options.PositionTop = 0.0f;
    options.ConsoleWidth = 16;
    options.ConsoleHeight = 2;
    options.ConsoleScale = 1.0f;
    options.Color = 0xFFFF64FF;
    options.DoDebugPrints = false;
    
    return new StatsConsole(options);
}

StatsConsole::StatsConsole(const DebugConsoleInitOptions& options) : DebugConsole(options){}

void StatsConsole::Update(float deltaTime) {
    this->PrintfPut("DELTA TIME -> %e\n", deltaTime);
}
