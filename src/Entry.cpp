// -------------------------------------------------
// The entry-point of the PSGLShading application.
// -------------------------------------------------

#include <sys/spu_initialize.h>
#include <sys/process.h>

#include "Core/Core.hpp"
#include "Core/DebugConsole.h"
#include "Core/DeltaTime.hpp"
#include "Rendering/Debug/StatsConsole.h"
#include "Core/Util/CELLCallbackHelpers.h"
#include "Input/PadUtility.h"
#include "Rendering/Renderer.h"

#include <cell/sysmodule.h>

#include "Rendering/Camera/PerspectiveCamera.h"
#include "Rendering/Camera/Debug/CameraInfoConsole.h"

//TODO: Figure out what this do...
SYS_PROCESS_PARAM(1001, 0x10000)

// ------------------------------------------
// Our "priority-ordered" list of resolutions
// to display our application at.
// ------------------------------------------
constexpr unsigned int resolutions[] = {
    CELL_VIDEO_OUT_RESOLUTION_1080, //HDMI Only
    CELL_VIDEO_OUT_RESOLUTION_720, //HDMI Only
};
PerspectiveCamera* worldCamera = nullptr;

static void EnableVSyncTEST() {
    Renderer::SetVSync(true);
}
static void DisableVSyncTEST() {
    Renderer::SetVSync(false);
}
static void MoveWorldCameraUP() {
    worldCamera->GetTransform().Position[0] += 0.1f;
}
static void MoveWorldCameraDOWN() {
    worldCamera->GetTransform().Position[0] -= 0.1f;
}
static void RotateWorldCameraX() {
    worldCamera->GetTransform().Rotation[0] += 0.1f;
}
static void RotateWorldCameraY() {
    worldCamera->GetTransform().Rotation[1] += 0.1f;
}

int main() {
    sys_spu_initialize(6, 1); //Setup SPUs (1 RAW SPU FOR PSGL)
    
    //Bind callbacks
    CELLCallbackHelpers::BindCallbacks();
    
    //Initialize the Renderer
    bool initResult = Renderer::Initialize(resolutions, sizeof(resolutions)/sizeof(resolutions[0]));
    if (!initResult) { return -1; } //Initialization failed, details have already been printed

    //Camera
    //PerspectiveCamera* worldCamera = new PerspectiveCamera(60.0f, 0.1f, 800.0f); TODO: REVERT
    worldCamera = new PerspectiveCamera(60.0f, 0.1f, 800.0f);
    Renderer::AddCamera(worldCamera);
    
    //Setup Pads
    PadUtility::Initialize(PAD_PLAYER_EIGHT);
    PadUtility::GetPad(PAD_PLAYER_ONE).SetPressedFunc(E_PAD_BUTTONS::CROSS, EnableVSyncTEST); //TODO: REMOVE
    PadUtility::GetPad(PAD_PLAYER_ONE).SetPressedFunc(E_PAD_BUTTONS::CIRCLE, DisableVSyncTEST); //TODO: REMOVE
    PadUtility::GetPad(PAD_PLAYER_ONE).SetPressedFunc(E_PAD_BUTTONS::DPAD_UP, MoveWorldCameraUP); //TODO: REMOVE
    PadUtility::GetPad(PAD_PLAYER_ONE).SetPressedFunc(E_PAD_BUTTONS::DPAD_DOWN, MoveWorldCameraDOWN); //TODO: REMOVE
    PadUtility::GetPad(PAD_PLAYER_ONE).SetPressedFunc(E_PAD_BUTTONS::DPAD_LEFT, RotateWorldCameraX); //TODO: REMOVE
    PadUtility::GetPad(PAD_PLAYER_ONE).SetPressedFunc(E_PAD_BUTTONS::DPAD_RIGHT, RotateWorldCameraY); //TODO: REMOVE
    
    //Debug Consoles
    StatsConsole* statsConsole = StatsConsole::Create();
    CameraInfoConsole* worldCamConsole = CameraInfoConsole::Create(worldCamera);
    
    //DeltaTime
    DeltaTime* deltaTime = new DeltaTime();
    
    while (!CELLCallbackHelpers::HasReceivedCloseCallback()) {
        CELLCallbackHelpers::CheckIncomingCallbacks();
        PadUtility::Update();
        float dt = deltaTime->UpdateDeltaTime(); //Update the DeltaTime
        
        Renderer::PreRender();
            DebugConsole::UpdateConsoles(dt);
            Renderer::Render(dt);
        Renderer::PostRender();
    }
    
    delete statsConsole;
    delete worldCamConsole;
    delete worldCamera;
    
    PadUtility::Dispose();
    Renderer::Shutdown();
    CELLCallbackHelpers::UnbindCallbacks();
    
    return 0; //Directly return into the XMB
}
