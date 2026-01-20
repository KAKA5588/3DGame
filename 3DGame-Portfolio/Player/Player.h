#pragma once
#include "../Actor/Actor.h"
#include "../Camera/Camera.h"

class Player : public Actor
{
public:
    Player();

    void Initialize() override;
    void Update(float dt) override;
    void Draw() override;

private:
    float moveSpeed;
    Camera camera;

    void HandleInput(float dt);
};
