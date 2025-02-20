#pragma once

#include <vectormath/cpp/vectormath_aos.h>

using namespace Vectormath::Aos;

class Transform final {
public:
    Vector3 Position;
    Vector3 Rotation;
    Vector3 Scale;

    inline void Update() {
        //TODO: Cancel the update if nothing has been modified?
        localToWorld =  Matrix4::translation(Position) *
                        Matrix4::rotationX(Rotation[0]) * Matrix4::rotationX(Rotation[1]) * Matrix4::rotationX(Rotation[2]) *
                        Matrix4::scale(Scale);
    }

    inline Matrix4& GetLocalToWorld() {
        return localToWorld;
    }
    
private:
    Matrix4 localToWorld;
};
