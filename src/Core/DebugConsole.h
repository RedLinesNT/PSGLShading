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
    // The buffer size of the DebugConsole's font.
    // ---------------------------------------------------------------------------
    uint32_t BufferSize = 512;

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
    // Should this DebugConsole use the DEBUG_PRINT macro when using
    // "Printf" or "vPrintf"?
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

    void Printf(const char* string, ...);
    void vPrintf(const char* string, va_list args);

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
    void Clear();

    // ---------------------------------------------------------------------------
    // Update and render each DebugConsoles created.
    // ---------------------------------------------------------------------------
    static void UpdateConsoles();
    
protected:
    virtual void Update() = 0;

private:
    // ---------------------------------------------------------------------------
    // Render this DebugConsoles.
    // ---------------------------------------------------------------------------
    void Render();

private:
    // ---------------------------------------------------------------------------
    // The name of this DebugConsole. Will be used to DEBUG_PRINT.
    // ---------------------------------------------------------------------------
    const char* consoleName;
    // ---------------------------------------------------------------------------
    // The "CellDbgFontConsoleId" of this debug console.
    // ---------------------------------------------------------------------------
    CellDbgFontConsoleId debugConsoleID;
    // ---------------------------------------------------------------------------
    // Is this DebugConsole currently enabled?
    // ---------------------------------------------------------------------------
    bool isEnabled;
    // ---------------------------------------------------------------------------
    // Should this DebugConsole use the DEBUG_PRINT macro when using
    // "Printf" or "vPrintf"?
    // ---------------------------------------------------------------------------
    bool doDebugPrints;

    // ---------------------------------------------------------------------------
    // Does the CELLDebugConsole has been internally initialized previously?
    // ---------------------------------------------------------------------------
    static bool hasBeenInitialized;
    // ---------------------------------------------------------------------------
    // List of every DebugConsoles created.
    // ---------------------------------------------------------------------------
    static std::list<DebugConsole*> consoles;
};
