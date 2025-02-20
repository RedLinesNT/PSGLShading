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
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspectivef(fieldOfView, Renderer::GetAspectRatio(), nearPlane, farPlane);

    needsRecalculateProjectionMatrix = false;
}
