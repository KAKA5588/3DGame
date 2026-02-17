#include "PlayerPhysics.h"
#include "Player.h"
#include "../Stage/Stage.h"
#include "DxLib.h"

constexpr float GRAVITY = -40.0f;
constexpr float WALL_CHECK_DIST = 6.0f;

static VECTOR ToVECTOR(const Vec3& v)
{
    return VGet(v.x, v.y, v.z);
}

void PlayerPhysics::Update(Player& player, Stage* stage, float dt)
{
    ApplyGravity(player, dt);

    Vec3 nextPos = player.position + player.velocity * dt;

    ResolveFloor(player, stage, nextPos);
    ResolveWall(player, stage, nextPos);

    player.position = nextPos;
}

void PlayerPhysics::ApplyGravity(Player& player, float dt)
{
    if (!player.isGrounded)
    {
        player.velocity.y += GRAVITY * dt;
    }
}

/*
----------------------------------
    床判定（下向きレイ）
----------------------------------
*/
void PlayerPhysics::ResolveFloor(Player& player, Stage* stage, Vec3& nextPos)
{
    player.isGrounded = false;
    if (!stage) return;
    if (player.velocity.y > 0.0f) return;

    VECTOR start = ToVECTOR({
        nextPos.x,
        player.position.y,
        nextPos.z
        });

    VECTOR end = ToVECTOR({
        nextPos.x,
        nextPos.y - radius - 5.0f,
        nextPos.z
        });

    auto hit = MV1CollCheck_Line(
        stage->GetModelHandle(),
        -1,
        start,
        end
    );

    float dist = start.y - hit.HitPosition.y;

    if (hit.HitPosition.y > -100000.0f &&
        dist >= 0.0f &&
        dist <= 20.0f)
    {
        nextPos.y = hit.HitPosition.y + radius;
        player.velocity.y = 0.0f;
        player.isGrounded = true;
    }
}

/*
----------------------------------
    壁判定（横方向4本）
----------------------------------
*/
void PlayerPhysics::ResolveWall(Player& player, Stage* stage, Vec3& nextPos)
{
    if (!stage) return;

    // 横移動していないなら壁判定しない
    Vec3 horizontalVel{ player.velocity.x, 0.0f, player.velocity.z };
    if (horizontalVel.Length() < 0.001f) return;

    Vec3 dir = horizontalVel.Normalized(); 

    //  足元ではなく腰の高さ
    Vec3 startPos{
        player.position.x,
        player.position.y + radius,
        player.position.z
    };

    Vec3 endPos = startPos + dir * 10.0f;

    VECTOR start = VGet(startPos.x, startPos.y, startPos.z);
    VECTOR end = VGet(endPos.x, endPos.y, endPos.z);

    auto hit = MV1CollCheck_Line(
        stage->GetModelHandle(),
        -1,
        start,
        end
    );

    if (hit.HitPosition.y > -100000.0f)
    {
        // 進行方向だけ止める
        nextPos.x = player.position.x;
        nextPos.z = player.position.z;

        player.velocity.x = 0.0f;
        player.velocity.z = 0.0f;
    }
}
