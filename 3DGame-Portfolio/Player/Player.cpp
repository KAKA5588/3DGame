#include "Player.h"

Player::Player()
    : moveSpeed(6.0f)
{
}

void Player::Initialize()
{
    camera.SetTarget(this);
}

void Player::Update(float dt)
{
    HandleInput(dt);
    camera.Update(dt);
}

void Player::Draw()
{
    // DrawPlayerModel ‚È‚Ç‚ÍŒã‚Å
}

void Player::HandleInput(float dt)
{
    // “ü—ÍEˆÚ“®ˆ—‚ÍŒã‚ÅÀ‘•
}
