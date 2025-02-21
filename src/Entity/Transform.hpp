#pragma once

#include <vectormath/cpp/vectormath_aos.h>

using namespace Vectormath::Aos;

class Transform final {
public:
    Vector3 Position;
    Vector3 Rotation;
    Vector3 Scale;

    Transform() : Position(0.0f, 0.0f, 0.0f), 
                  Rotation(0.0f, 0.0f, 0.0f), 
                  Scale(1.0f, 1.0f, 1.0f) {}
    Transform(const Vector3& pos, const Vector3& rot, const Vector3& scl) : Position(pos), Rotation(rot), Scale(scl) {}

    
    inline void Update() {
        //TODO: Cancel the update if nothing has been modified?
        localToWorld =  Matrix4::translation(Position) *
                        Matrix4::rotationX(Rotation.getX()) * Matrix4::rotationY(Rotation.getY()) * Matrix4::rotationZ(Rotation.getZ()) *
                        Matrix4::scale(Scale);
    }

    inline Matrix4& GetLocalToWorld() {
        return localToWorld;
    }
    
private:
    Matrix4 localToWorld;
};
