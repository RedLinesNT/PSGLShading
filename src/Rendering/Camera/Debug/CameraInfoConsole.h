#pragma once
#include "Core/DebugConsole.h"

// ---------------------------------------------------
// Display some information about the
// Camera::mainCamera.
// ---------------------------------------------------
class CameraInfoConsole final : public DebugConsole {
public:
    CameraInfoConsole(const DebugConsoleInitOptions& options);
    virtual ~CameraInfoConsole() = default;

    // ---------------------------------------------------------------------------
    // Create a "CameraInfoConsole" with default settings.
    // ---------------------------------------------------------------------------
    static CameraInfoConsole* Create();
protected:
    void Update(float deltaTime) override;
};
