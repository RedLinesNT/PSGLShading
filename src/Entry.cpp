// -------------------------------------------------
// The entry-point of the PSGLShading application.
// -------------------------------------------------

#include <sys/spu_initialize.h>
#include "Rendering/GraphicsContext.h"
#include "Core/Core.h"
#include "Core/DebugConsole.h"
#include "Core/DeltaTime.h"
#include "Core/Debug/StatsConsole.h"

#include <sys/process.h>

SYS_PROCESS_PARAM(1001, 0x10000) //TODO: Figure out what is this...

// ------------------------------------------
// Our "priority-ordered" list of resolutions
// to display our application at.
// ------------------------------------------
constexpr unsigned int resolutions[] = {
    CELL_VIDEO_OUT_RESOLUTION_1080, //HDMI Only
    CELL_VIDEO_OUT_RESOLUTION_720, //HDMI Only
};

// ---------------------------------------------------------------------------
// Will be set to true if the user or PlayStation3 is trying to
// close/shutdown this application.
// ---------------------------------------------------------------------------
static bool ShouldClose = false;

// ---------------------------------------------------------------------------
// Handle some specific CELL's callbacks.
// ---------------------------------------------------------------------------
// Remarks:
//      Only used to exit the application's "while(true)" loop.
//      If this method isn't called to stop the application from running,
//      the PlayStation3 will freeze upon trying to close the app, then
//      forcefully reboot itself.
// ---------------------------------------------------------------------------
static void HandleCELLCloseCallback(uint64_t status, uint64_t param, void* userdata) {
    (void)param;
    (void)userdata;

    if (status == CELL_SYSUTIL_REQUEST_EXITGAME) {
        ShouldClose = true;
        DEBUG_PRINT("[PSGLShading] CELL_SYSUTIL_REQUEST_EXITGAME Callback received! Shutting down...\n")
    }
}

int main() {
    sys_spu_initialize(6, 1); //Setup SPUs
    cellSysutilRegisterCallback(0, HandleCELLCloseCallback, nullptr); //Setup shutdown callback (SLOT 0)

    //Initialize the GraphicsContext
    GraphicsContext* context = new GraphicsContext();
    bool initResult = context->Initialize(resolutions, sizeof(resolutions)/sizeof(resolutions[0]));
    if (!initResult) { return -1; } //Initialization failed, details have already been printed
    DEBUG_PRINT("[PSGLShading] Graphics Context has been initialized!\n")

    //Debug Consoles
    StatsConsole* statsConsole = StatsConsole::Create();
    
    //DeltaTime
    DeltaTime* deltaTime = new DeltaTime();

    while (!ShouldClose) {
        cellSysutilCheckCallback(); //Check for incoming system's callbacks
        float dt = deltaTime->UpdateDeltaTime(); //Update the DeltaTime
        
        context->PreRender();
            DebugConsole::UpdateConsoles(dt);
        
            //TODO: Render context
        context->PostRender();
    }
    
    delete statsConsole;
    context->Dispose();
    
    cellSysutilUnregisterCallback(0); //Unregister the shutdown callback (SLOT 0)
    
    return 0; //Directly return into the XMB
}
