#pragma once
#include "DxLib.h"
#include "../Actor/Actor.h"

class Camera
{
public:
    Camera();

    void SetTarget(Actor* actor);
    void Initialize();
    void Update(float dt);
    void Apply();

    float GetYaw() const { return yaw; }

private:
    Actor* target = nullptr;

    // 回転
    float yaw;
    float pitch;

    // ===== 調整用（ヘッダーで触る）=====
    float distance;        // プレイヤーとの距離（固定）
    float targetHeight;    // 注視点の高さ

    float mouseSensitivity;

    float pitchMin;
    float pitchMax;
    // ====================================

    VECTOR position;
};
