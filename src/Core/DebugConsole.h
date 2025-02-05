#pragma once
#include <list>
#include <cell/dbgfont.h>

// ---------------------------------------------------
// The initialization options for the "DebugConsole".
// ---------------------------------------------------
struct DebugConsoleInitOptions {
    // ---------------------------------------------------------------------------
    // The name of this DebugConsole, will be used to "DEBUG_PRINT"
    // throughout method calls.
    // ---------------------------------------------------------------------------
    const char* Name;
    
    // ---------------------------------------------------------------------------
    // The left position of the DebugConsole.
    // ---------------------------------------------------------------------------
    float PositionLeft = 0.1f;
    // ---------------------------------------------------------------------------
    // The top position of the DebugConsole.
    // ---------------------------------------------------------------------------
    float PositionTop = 0.8f;

    // ---------------------------------------------------------------------------
    // The width of the DebugConsole.
    // ---------------------------------------------------------------------------
    uint32_t ConsoleWidth = 16;
    // ---------------------------------------------------------------------------
    // The height of the DebugConsole.
    // ---------------------------------------------------------------------------
    uint32_t ConsoleHeight = 4;
    // ---------------------------------------------------------------------------
    // The scale of the DebugConsole.
    // ---------------------------------------------------------------------------
    float ConsoleScale = 0.25f;
    // ---------------------------------------------------------------------------
    // The scale of the DebugConsole's text.
    // ---------------------------------------------------------------------------
    float ConsoleTextScale = 0.25f;

    // ---------------------------------------------------------------------------
    // The DebugConsole's font color.
    // ---------------------------------------------------------------------------
    // Remarks:
    //      This is a hexadecimal (little-endian) RGBA value.
    // ---------------------------------------------------------------------------
    //  Example:
    //      I want a pink color, the RGBA value will be "rgba(255, 100, 255, 255)".
    //      In hexadecimal, the value will be "FF64FFFF". But because the
    //      PlayStation3 uses big endianness, my value at the end will be
    //      "FFFF64FF", or "abgr(255, 255, 100, 255)".
    // ---------------------------------------------------------------------------
    uint32_t Color = 0xFFFF64FF;

    // ---------------------------------------------------------------------------
    // Should this DebugConsole use the DEBUG_PRINT macro when using "Printf"?
    // ---------------------------------------------------------------------------
    bool DoDebugPrints = true;
};

// ---------------------------------------------------
// DebugConsole is a CELLDebugConsole
// made to display various information in various
// places.
// ---------------------------------------------------
// Remarks:
//      The DebugConsole can be extended for various
//      usages.
//      "DebugConsole->Enable" is automatically
//      invoked at creation, and "DebugConsole->Disable"
//      at destruction.
// ---------------------------------------------------
class DebugConsole {
public:
    DebugConsole(const DebugConsoleInitOptions& options);
    ~DebugConsole();

    void Printf(const char* string, ...) const;
    void PrintfPut(const char* string, ...) const;

    // ---------------------------------------------------------------------------
    // Enable this DebugConsole.
    // ---------------------------------------------------------------------------
    void Enable();
    // ---------------------------------------------------------------------------
    // Disable of the DebugConsole.
    // ---------------------------------------------------------------------------
    void Disable();
    // ---------------------------------------------------------------------------
    // Clear of the DebugConsole.
    // ---------------------------------------------------------------------------
    void Clear() const;

    // ---------------------------------------------------------------------------
    // Update and render each DebugConsoles created.
    // ---------------------------------------------------------------------------
    static void UpdateConsoles();

private:
    // ---------------------------------------------------------------------------
    // The "DebugConsoleInitOptions" given to create this DebugConsole.
    // ---------------------------------------------------------------------------
    const DebugConsoleInitOptions& initOptions;
    // ---------------------------------------------------------------------------
    // The "CellDbgFontConsoleId" of this DebugConsole.
    // ---------------------------------------------------------------------------
    CellDbgFontConsoleId debugConsoleID;
    // ---------------------------------------------------------------------------
    // Is this DebugConsole currently enabled?
    // ---------------------------------------------------------------------------
    bool isEnabled;

    // ---------------------------------------------------------------------------
    // List of every DebugConsoles created.
    // ---------------------------------------------------------------------------
    static std::list<DebugConsole*> consoles;
    // ---------------------------------------------------------------------------
    // Has "cellDbg" already been initialized?
    // ---------------------------------------------------------------------------
    static bool hasBeenInitialized;
};
