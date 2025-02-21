#include "CameraInfoConsole.h"

#include "Rendering/Camera/PerspectiveCamera.h"

CameraInfoConsole::CameraInfoConsole(const DebugConsoleInitOptions& options, Camera* camera) : targetCamera(camera), DebugConsole(options) {}

CameraInfoConsole* CameraInfoConsole::Create(Camera* targetCamera) {
    DebugConsoleInitOptions options;
    options.Name = "CameraInfoConsole";
    options.PositionLeft = 0.7f;
    options.PositionTop = 0.0f;
    options.ConsoleWidth = 35;
    options.ConsoleHeight = 3;
    options.ConsoleScale = 0.65f;
    options.Color = 0xFFFFFFFF;
    options.DoDebugPrints = false;
    
    return new CameraInfoConsole(options, targetCamera);
}

void CameraInfoConsole::Update(float deltaTime) { //TODO: Modify this mess, this ain't C# ffs
    if (targetCamera == nullptr) return;

    //TODO: What the fuck
    PerspectiveCamera* pers = static_cast<PerspectiveCamera*>(targetCamera);
    
    if (pers != nullptr) {
        this->PrintfPut("FOV: %.1f / FAR: %.1f / NEAR: %.1f",
                        pers->GetFieldOfView(), pers->GetFarPlane(), pers->GetNearPlane());
    }

    this->PrintfPut("\nPOS: %.1f, %.1f, %.1f",
                    targetCamera->GetTransform().Position.getX().getAsFloat(),
                    targetCamera->GetTransform().Position.getY().getAsFloat(),
                    targetCamera->GetTransform().Position.getZ().getAsFloat());

    this->PrintfPut("\n\nROT: %.1f, %.1f, %.1f",
                    targetCamera->GetTransform().Rotation.getX().getAsFloat(),
                    targetCamera->GetTransform().Rotation.getY().getAsFloat(),
                    targetCamera->GetTransform().Rotation.getZ().getAsFloat());

    this->PrintfPut("\n\n\nSCALE: %.1f, %.1f, %.1f",
                    targetCamera->GetTransform().Scale.getX().getAsFloat(),
                    targetCamera->GetTransform().Scale.getY().getAsFloat(),
                    targetCamera->GetTransform().Scale.getZ().getAsFloat());
}
