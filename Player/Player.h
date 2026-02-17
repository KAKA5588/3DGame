#pragma once
#include "../Actor/Actor.h"

class Stage;
class Camera;   // Åö í«â¡

class Player : public Actor
{
public:
    Player();
    ~Player();

    void Initialize() override;
    void Update(float dt) override;
    void Draw() override;

    void SetStage(Stage* stage);
    void SetCamera(Camera* camera);   // Åö í«â¡

private:
    Stage* stage = nullptr;
    Camera* camera = nullptr;         // Åö í«â¡

    int Player_handle = -1;

    float moveSpeed;
    float radius;
    bool isGrounded;

    void HandleInput(float dt);
    void ApplyGravity(float dt);

    // Åö è∞îªíË
    void CollisionWithFloor(Vec3& nextPos);
};
