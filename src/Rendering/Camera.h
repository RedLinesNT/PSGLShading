﻿#pragma once
#include "Renderer.h"
#include "Entity/Transform.hpp"

enum E_CAMERA_TYPE {
    CAM_TYPE_PERSPECTIVE = 0,
    CAM_TYPE_ORTHOGRAPHIC = 1,
};

class Camera {
public:
    inline Camera(const E_CAMERA_TYPE type) {
        this->type = type;
        transform = new Transform();
        needsRecalculateProjectionMatrix = true;
        Renderer::AddCamera(this);
    }
    virtual inline ~Camera() {
        Renderer::RemoveCamera(this);
        delete transform;
    }

    // ---------------------------------------------------------------------------
    // Recalculate/Set its Projection Matrix.
    // ---------------------------------------------------------------------------
    virtual void RecalculateProjectionMatrix() = 0;

    // ---------------------------------------------------------------------------
    // Does this Camera need to recalculate its Projection Matrix.
    // ---------------------------------------------------------------------------
    inline bool NeedRecalculateProjectionMatrix() const { return needsRecalculateProjectionMatrix; }
    inline Transform& GetTransform() const { return *transform; }
    // ---------------------------------------------------------------------------
    // Returns the Projection Matrix of this Camera.
    // ---------------------------------------------------------------------------
    inline Matrix4 GetProjectionMatrix() const { return projectionMatrix; }
protected:
    Transform* transform;
    E_CAMERA_TYPE type;
    // ---------------------------------------------------------------------------
    // Does this Camera need to recalculate its Projection Matrix.
    // ---------------------------------------------------------------------------
    bool needsRecalculateProjectionMatrix;

    // ---------------------------------------------------------------------------
    // The Projection Matrix of this Camera.
    // ---------------------------------------------------------------------------
    Matrix4 projectionMatrix;
};
