#pragma once
#include "../Vec3/Vec3.h"
#include "../Actor/Actor.h"

class Actor;

class Camera
{
public:
    Camera();

    void SetTarget(Actor* actor);
    void Update(float dt);

    float GetYaw() const;

private:
    Actor* target = nullptr;

    float distance;
    float height;

    float yaw;
    float pitch;

    Vec3 cameraPos;
};