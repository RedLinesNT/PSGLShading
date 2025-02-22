#pragma once
#include "Renderer.h"
#include "Core/Core.hpp"
#include "Entity/Transform.hpp"

enum E_CAMERA_TYPE {
    CAM_TYPE_PERSPECTIVE = 0,
    CAM_TYPE_ORTHOGRAPHIC = 1,
};

class Camera {
public:
    Camera(const E_CAMERA_TYPE type);
    virtual ~Camera();

    // ---------------------------------------------------------------------------
    // Recalculate/Set its Projection Matrix.
    // ---------------------------------------------------------------------------
    virtual void RecalculateProjectionMatrix() = 0;

    // ---------------------------------------------------------------------------
    // Calculate and give the View Matrix of this Camera.
    // ---------------------------------------------------------------------------
    // Remarks:
    //      Calling this method will CALCULATE the View Matrix, avoid calling
    //      it too many times for no reason.
    //
    //      The scale of this Camera's Transform isn't taken in account.
    // ---------------------------------------------------------------------------
    Matrix4 GetViewMatrix() const;
    
    inline Transform& GetTransform() const { return *transform; }
    inline E_CAMERA_TYPE GetType() const { return type; }
    // ---------------------------------------------------------------------------
    // Does this Camera need to recalculate its Projection Matrix.
    // ---------------------------------------------------------------------------
    inline bool NeedRecalculateProjectionMatrix() const { return needsRecalculateProjectionMatrix; }
    // ---------------------------------------------------------------------------
    // Returns the Projection Matrix of this Camera.
    // ---------------------------------------------------------------------------
    inline Matrix4 GetProjectionMatrix() const { return projectionMatrix; }

    // ---------------------------------------------------------------------------
    // Returns the main/active Camera. 
    // ---------------------------------------------------------------------------
    // Remarks:
    //      Only this Camera will be used for rendering.
    // ---------------------------------------------------------------------------
    inline static Camera* GetMainCamera() { return mainCamera; }
    // ---------------------------------------------------------------------------
    // Sets the main/active Camera.
    // ---------------------------------------------------------------------------
    // Remarks:
    //      Only this Camera will be used for rendering.
    // ---------------------------------------------------------------------------
    inline static void SetMainCamera(Camera* cam) { mainCamera = cam; DEBUG_PRINT("[Camera] Main Camera set.\n") }
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

private:
    // ---------------------------------------------------------------------------
    // The main/active Camera. 
    // ---------------------------------------------------------------------------
    // Remarks:
    //      Only this Camera will be used for rendering.
    // ---------------------------------------------------------------------------
    static Camera* mainCamera;
};
