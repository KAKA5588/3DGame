#pragma once
#include <memory>
#include "../Vec3/Vec3.h"

class Actor
{
public:
    Vec3 position;
    Vec3 rotation;   // pitch, yaw, roll
    Vec3 scale{ 1,1,1 };
    Vec3 velocity;

    bool isAlive = true;

    virtual ~Actor() {}

    virtual void Initialize() {}
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;

    // 3D—p
    virtual Vec3 GetForward() const
    {
        return Vec3(
            sinf(rotation.y),
            0.0f,
            cosf(rotation.y)
        );
    }
};
