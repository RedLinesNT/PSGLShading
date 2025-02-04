// -------------------------------------------------
// The entry-point of the PSGLShading application.
// -------------------------------------------------

#include <sys/spu_initialize.h>
#include "Rendering/GraphicsContext.h"
#include "Core/Core.h"

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
    Rendering::GraphicsContext* context = new Rendering::GraphicsContext();
    bool initResult = Rendering::GraphicsContext::Get()->Initialize(resolutions, sizeof(resolutions)/sizeof(resolutions[0]));
    if (!initResult) { return -1; } //Initialization failed, details have already been printed
    DEBUG_PRINT("[PSGLShading] Graphics Context has been initialized!")

    while (true) {
        Rendering::GraphicsContext::Get()->PreRender();
        //TODO: Render context
        Rendering::GraphicsContext::Get()->PostRender();
    }
    
    return 0; //Directly return into the XMB
}
