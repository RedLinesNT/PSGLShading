#include "CameraInfoConsole.h"

#include "Rendering/Camera/PerspectiveCamera.h"

CameraInfoConsole* CameraInfoConsole::Create() {
    DebugConsoleInitOptions options;
    options.Name = "CameraInfoConsole";
    options.PositionLeft = 0.7f;
    options.PositionTop = 0.0f;
    options.ConsoleWidth = 35;
    options.ConsoleHeight = 3;
    options.ConsoleScale = 0.65f;
    options.Color = 0xFFFFFFFF;
    options.DoDebugPrints = false;
    
    return new CameraInfoConsole(options);
}

CameraInfoConsole::CameraInfoConsole(const DebugConsoleInitOptions& options) : DebugConsole(options) {}

void CameraInfoConsole::Update(float deltaTime) { //TODO: Modify this mess
    if (Camera::GetMainCamera() == nullptr) return;

    //TODO: What the fuck, I'll regret this soon ?
    if (Camera::GetMainCamera()->GetType() == E_CAMERA_TYPE::CAM_TYPE_PERSPECTIVE) {
        auto* pers = static_cast<PerspectiveCamera*>(Camera::GetMainCamera());
        this->PrintfPut("FOV: %.1f / FAR: %.1f / NEAR: %.1f",
                        pers->GetFieldOfView(), pers->GetFarPlane(), pers->GetNearPlane());
    }

    this->PrintfPut("\nPOS: %.1f, %.1f, %.1f",
                    Camera::GetMainCamera()->GetTransform().Position.getX().getAsFloat(),
                    Camera::GetMainCamera()->GetTransform().Position.getY().getAsFloat(),
                    Camera::GetMainCamera()->GetTransform().Position.getZ().getAsFloat());

    this->PrintfPut("\n\nROT: %.1f, %.1f, %.1f",
                    Camera::GetMainCamera()->GetTransform().Rotation.getX().getAsFloat(),
                    Camera::GetMainCamera()->GetTransform().Rotation.getY().getAsFloat(),
                    Camera::GetMainCamera()->GetTransform().Rotation.getZ().getAsFloat());

    this->PrintfPut("\n\n\nSCALE: %.1f, %.1f, %.1f",
                    Camera::GetMainCamera()->GetTransform().Scale.getX().getAsFloat(),
                    Camera::GetMainCamera()->GetTransform().Scale.getY().getAsFloat(),
                    Camera::GetMainCamera()->GetTransform().Scale.getZ().getAsFloat());
}
