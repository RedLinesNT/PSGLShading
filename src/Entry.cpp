// -------------------------------------------------
// The entry-point of the PSGLShading application.
// -------------------------------------------------

#include <sys/spu_initialize.h>
#include "Rendering/GraphicsContext.h"
#include "Core/Core.h"
#include "Core/DebugConsole.h"
#include "Core/DeltaTime.h"
#include "Core/Debug/StatsConsole.h"

// ------------------------------------------
// Our "priority-ordered" list of resolutions
// to display our application at.
// ------------------------------------------
constexpr unsigned int resolutions[] = {
    CELL_VIDEO_OUT_RESOLUTION_1080, //HDMI Only
    CELL_VIDEO_OUT_RESOLUTION_720, //HDMI Only
};

int main() {
    sys_spu_initialize(6, 1); //Setup SPUs

    //Initialize the GraphicsContext
    GraphicsContext* context = new GraphicsContext();
    bool initResult = context->Initialize(resolutions, sizeof(resolutions)/sizeof(resolutions[0]));
    if (!initResult) { return -1; } //Initialization failed, details have already been printed
    DEBUG_PRINT("[PSGLShading] Graphics Context has been initialized!\n")

    //Debug Consoles
    StatsConsole* statsConsole = StatsConsole::Create();
    
    //DeltaTime
    DeltaTime* deltaTime = new DeltaTime();

    while (true) {
        //Update the DeltaTime
        float dt = deltaTime->UpdateDeltaTime();
        
        context->PreRender();
            DebugConsole::UpdateConsoles(dt);
        
            //TODO: Render context
        context->PostRender();
    }
    
    delete statsConsole;
    context->Dispose();
    
    return 0; //Directly return into the XMB
}
