#include "DebugConsole.h"

bool DebugConsole::hasBeenInitialized = false;
std::list<DebugConsole*> DebugConsole::consoles;

DebugConsole::DebugConsole(const DebugConsoleInitOptions& options) {
    consoleName = options.Name;
    doDebugPrints = options.DoDebugPrints;
    
    //TODO: Init

    consoles.push_back(this);
}

DebugConsole::~DebugConsole() {
    consoles.remove(this);
    //TODO: De-Init
}

void DebugConsole::UpdateConsoles() {
    for (DebugConsole* console : consoles) {
        console->Update();
        console->Render();
    }
}

void DebugConsole::Render() {
    //TODO: Render
}

void DebugConsole::Enable() {
    //TODO: Enable
}

void DebugConsole::Disable() {
    //TODO: Disable
}

void DebugConsole::Clear() {
    //TODO: Clear
}

void DebugConsole::Printf(const char* string, ...) {
    
}








