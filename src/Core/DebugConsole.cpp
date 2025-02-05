#include "DebugConsole.h"

#include "Core.h"
#include "Rendering/GraphicsContext.h"

std::list<DebugConsole*> DebugConsole::consoles;
bool DebugConsole::hasBeenInitialized = false;

DebugConsole::DebugConsole(const DebugConsoleInitOptions& options): initOptions(options) {
    if (!hasBeenInitialized) {
        //Initialize CellDbg
        CellDbgFontConfig fontConfig;
        fontConfig.screenWidth = GraphicsContext::GetViewportWidth();
        fontConfig.screenHeight = GraphicsContext::GetViewportHeight();
        
        cellDbgFontInit(&fontConfig);
        hasBeenInitialized = true;
    }
    
    CellDbgFontConsoleConfig consoleConfig;
    consoleConfig.posLeft = initOptions.PositionLeft;
    consoleConfig.posTop = initOptions.PositionTop;
    consoleConfig.cnsWidth = initOptions.ConsoleWidth;
    consoleConfig.cnsHeight = initOptions.ConsoleHeight;
    consoleConfig.scale = initOptions.ConsoleScale;
    consoleConfig.color = initOptions.Color;

    debugConsoleID = cellDbgFontConsoleOpen(&consoleConfig);
    consoles.push_back(this);

    DEBUG_PRINT("[DebugConsole (%s)] Console created.\n", initOptions.Name)
}

DebugConsole::~DebugConsole() {
    consoles.remove(this);
    cellDbgFontConsoleClose(debugConsoleID);

    if (consoles.empty()) {
        hasBeenInitialized = false;
        cellDbgFontExit();
    }
}

void DebugConsole::UpdateConsoles() {
    /*for (DebugConsole* console : consoles) {
        console->Update();
    }*/

    cellDbgFontDraw();
}

void DebugConsole::Enable() {
    isEnabled = true;
    cellDbgFontConsoleEnable(debugConsoleID);
}

void DebugConsole::Disable() {
    isEnabled = false;
    cellDbgFontConsoleDisable(debugConsoleID);
}

void DebugConsole::Clear() const {
    cellDbgFontConsoleClear(debugConsoleID);
}

void DebugConsole::Printf(const char* string, ...) const {
    char temp_str[1024];
    
    va_list arg_list;
    va_start(arg_list, string);
    vsprintf(temp_str, string, arg_list);
    va_end(arglist);

    cellDbgFontConsolePrintf(debugConsoleID, temp_str);
    if (initOptions.DoDebugPrints) DEBUG_PRINT("[DebugConsole (%s)] %s\n", initOptions.Name, temp_str)
}

void DebugConsole::PrintfPut(const char* string, ...) const {
    char temp_str[1024];
    
    va_list arg_list;
    va_start(arg_list, string);
    vsprintf(temp_str, string, arg_list);
    va_end(arglist);

    cellDbgFontPuts(initOptions.PositionLeft, initOptions.PositionTop,
                    initOptions.ConsoleScale, initOptions.Color, temp_str);
    if (initOptions.DoDebugPrints) DEBUG_PRINT("[DebugConsole (%s)] %s\n", initOptions.Name, temp_str)
}









