#pragma once

class Player;
class Camera;

class PlayerController
{
public:
    void Update(Player& player, Camera* camera);

private:
    float moveSpeed = 300.0f;
};
