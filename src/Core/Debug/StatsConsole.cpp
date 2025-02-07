#include "StatsConsole.h"

#include "Core/Util/CELLCallbackHelpers.h"

StatsConsole* StatsConsole::Create() {
    DebugConsoleInitOptions options;
    options.Name = "StatsConsole";
    options.PositionLeft = 0.0025f;
    options.PositionTop = 0.0025f;
    options.ConsoleWidth = 20;
    options.ConsoleHeight = 10;
    options.ConsoleScale = 1.0f;
    options.Color = 0xFFFFFFFF;
    options.DoDebugPrints = false;
    
    return new StatsConsole(options);
}


StatsConsole::StatsConsole(const DebugConsoleInitOptions& options) : DebugConsole(options) {
    framerate = 0;
    updateTimeElapsed = 0.0f;

    updateTimeInterval = 2.0f; //2 seconds between each update.
}

void StatsConsole::Update(float deltaTime) {    
    if (updateTimeElapsed >= updateTimeInterval) { //Update values at the correct interval
        framerate = 1.0f / deltaTime; //Framerate
        
        updateTimeElapsed = 0;
    }

    //Print the final result of everything
    this->PrintfPut("Framerate: %.1f\n"
                    "DT: %.5f",
                    framerate, deltaTime);

    this->PrintfPut("\n\nXMB opened? %s\n", CELLCallbackHelpers::IsTheXMBOpen() ? "true" : "false");
    
    updateTimeElapsed += deltaTime;
}
