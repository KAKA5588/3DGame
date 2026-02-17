#pragma once
#include "DxLib.h"
#include "EnemyStateMachine.h"

class Enemy
{
public:
    Enemy();

    void Initialize();
    void Update(float dt);
    void Draw();

    VECTOR GetPosition() const { return position; }

private:
    VECTOR position{};
    VECTOR size{ 30.0f, 80.0f, 30.0f };

    EnemyStateMachine stateMachine;
};
