#include "PerspectiveCamera.h"

#include "PSGL/psgl.h"
#include "PSGL/psglu.h"
#include "Rendering/Renderer.h"

PerspectiveCamera::PerspectiveCamera(float fov, float near, float far) : Camera(CAM_TYPE_PERSPECTIVE) {
    farPlane = far;
    nearPlane = near;
    fieldOfView = fov;
}

void PerspectiveCamera::RecalculateProjectionMatrix() {
    projectionMatrix = Matrix4::perspective(fieldOfView * (M_PI / 180.0f), Renderer::GetAspectRatio(), nearPlane, farPlane);
    needsRecalculateProjectionMatrix = false;
}
