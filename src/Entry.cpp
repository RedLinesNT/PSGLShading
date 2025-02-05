// -------------------------------------------------
// The entry-point of the PSGLShading application.
// -------------------------------------------------

#include <sys/spu_initialize.h>
#include "Rendering/GraphicsContext.h"
#include "Core/Core.h"
#include "Core/DebugConsole.h"

// ------------------------------------------
// Our "priority-ordered" list of resolutions
// to display our application at.
// ------------------------------------------
constexpr unsigned int resolutions[] = {
    CELL_VIDEO_OUT_RESOLUTION_1080,
    CELL_VIDEO_OUT_RESOLUTION_720,
};

int main() {
    sys_spu_initialize(6, 1); //Setup SPUs

    //Initialize the GraphicsContext
    GraphicsContext* context = new GraphicsContext();
    bool initResult = context->Initialize(resolutions, sizeof(resolutions)/sizeof(resolutions[0]));
    if (!initResult) { return -1; } //Initialization failed, details have already been printed
    DEBUG_PRINT("[PSGLShading] Graphics Context has been initialized!\n")

    //TODO: REMOVE
    DebugConsoleInitOptions test2Options;
    test2Options.Name = "TEST 2";
    test2Options.PositionLeft = 0.2f;
    test2Options.PositionTop = 0.1f;
    test2Options.ConsoleWidth = 16;
    test2Options.ConsoleHeight = 4;
    test2Options.ConsoleScale = 1.0f;
    test2Options.Color = 0xFF64FFFF;
    test2Options.DoDebugPrints = false;
    DebugConsole* test2 = new DebugConsole(test2Options);
    
    DebugConsoleInitOptions testOptions;
    testOptions.Name = "TEST 1";
    testOptions.PositionLeft = 0.1f;
    testOptions.PositionTop = 0.2f;
    testOptions.ConsoleWidth = 50;
    testOptions.ConsoleHeight = 5;
    testOptions.ConsoleScale = 1.0f;
    testOptions.Color = 0xFFFF64FF;
    testOptions.DoDebugPrints = false;
    
    DebugConsole* test = new DebugConsole(testOptions);

int i=0;
    
    while (true) {
        context->PreRender();
        DebugConsole::UpdateConsoles();
        
        test->Printf("TESTING A PF INTO THE CONSOLE! (I=%u)\n", i);
        test2->PrintfPut("TESTING A PUT SOMEWHERE (I=%u)\n", i);

        if (i == 1000) {
            test->Clear();
            test2->Clear();
        }

        if (i == 2000) {
            test->Disable();
        }

        if (i == 3000) {
            test->Enable();
            test->Clear();
            test2->Clear();

            i=0;
        }
        
        //TODO: Render context
        context->PostRender();

        i++;
    }

    delete test;
    context->Dispose();
    
    return 0; //Directly return into the XMB
}
