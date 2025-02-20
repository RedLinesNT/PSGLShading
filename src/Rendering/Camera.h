#pragma once
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
    }
    virtual inline ~Camera() { delete transform; }

    // ---------------------------------------------------------------------------
    // Recalculate/Set the View Projection Matrix of this Camera.
    // ---------------------------------------------------------------------------
    virtual void RecalculateProjectionMatrix() = 0;

    // ---------------------------------------------------------------------------
    // Does this Camera need to recalculate its Projection Matrix.
    // ---------------------------------------------------------------------------
    inline bool NeedRecalculateProjectMatrix() const { return needsRecalculateProjectionMatrix; }
    inline Transform& GetTransform() const { return *transform; }
protected:
    Transform* transform;
    E_CAMERA_TYPE type;
    // ---------------------------------------------------------------------------
    // Does this Camera need to recalculate its Projection Matrix.
    // ---------------------------------------------------------------------------
    bool needsRecalculateProjectionMatrix;
};
