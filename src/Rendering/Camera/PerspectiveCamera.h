#pragma once

#include "Rendering/Camera.h"

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(float fov, float near, float far);
    
    void RecalculateProjectionMatrix() override;

    inline float GetFarPlane() const { return farPlane; }
    inline void SetFarPlane(const float value) { farPlane = value; needsRecalculateProjectionMatrix = true; }

    inline float GetNearPlane() const { return nearPlane; }
    inline void SetNearPlane(const float value) { nearPlane = value; needsRecalculateProjectionMatrix = true; }

    inline float GetFieldOfView() const { return fieldOfView; }
    inline void SetFieldOfView(const float value) { fieldOfView = value; needsRecalculateProjectionMatrix = true; }

private:
    float farPlane;
    float nearPlane;
    float fieldOfView;
};