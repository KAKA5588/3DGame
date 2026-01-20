#include "Camera.h"
#include "../Actor/Actor.h"

Camera::Camera()
    : distance(6.0f)
    , height(2.0f)
    , yaw(0.0f)
    , pitch(20.0f)
    , cameraPos{}
{
}

void Camera::SetTarget(Actor* actor)
{
    target = actor;
}

void Camera::Update(float dt)
{
    if (!target) return;

    // ※ 後でマウス入力やDxLibのカメラ処理を書く
}

float Camera::GetYaw() const
{
    return yaw;
}
