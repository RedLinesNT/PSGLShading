#include "StatsConsole.h"

#include "Core/Util/CELLCallbackHelpers.h"
#include "Rendering/Context/GraphicsContext.h"

StatsConsole* StatsConsole::Create() {
    DebugConsoleInitOptions options;
    options.Name = "StatsConsole";
    options.PositionLeft = 0.0f;
    options.PositionTop = 0.0f;
    options.ConsoleWidth = 20;
    options.ConsoleHeight = 10;
    options.ConsoleScale = 0.9f;
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
    this->PrintfPut("%ux%u (%.1f FPS)", GraphicsContext::GetViewportWidth(), GraphicsContext::GetViewportHeight(), framerate);
    this->PrintfPut("\nDT: %.5f", deltaTime);
    
    this->PrintfPut("\n\nXMB opened? %s", CELLCallbackHelpers::IsTheXMBOpen() ? "true" : "false");
    
    updateTimeElapsed += deltaTime;
}
