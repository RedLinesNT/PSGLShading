#pragma once
#include "Core/DebugConsole.h"
#include "Rendering/Camera.h"

// ---------------------------------------------------
// Display some information about a Camera.
// ---------------------------------------------------
class CameraInfoConsole final : public DebugConsole {
public:
    CameraInfoConsole(const DebugConsoleInitOptions& options, Camera* camera);
    virtual ~CameraInfoConsole() = default;

    // ---------------------------------------------------------------------------
    // Create a "CameraInfoConsole" with default settings.
    // ---------------------------------------------------------------------------
    static CameraInfoConsole* Create(Camera* targetCamera);
protected:
    void Update(float deltaTime) override;

private:
    Camera* targetCamera;    
};
