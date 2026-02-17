#include "Player.h"
#include "../Stage/Stage.h"
#include "../Camera/Camera.h"
#include "DxLib.h"
#include <cmath>

constexpr float GRAVITY = -40.0f;

Player::Player()
{
    moveSpeed = 300.0f;
    radius = 5.0f;
    isGrounded = false;
    velocity = { 0,0,0 };
}

Player::~Player()
{
    if (Player_handle != -1)
    {
        MV1DeleteModel(Player_handle);
        Player_handle = -1;
    }
}

void Player::SetStage(Stage* s)
{
    stage = s;
}

void Player::SetCamera(Camera* cam)
{
    camera = cam;
}

void Player::Initialize()
{
    Player_handle = MV1LoadModel("Resource/Player/Player.pmd");
    if (Player_handle == -1)
    {
        printfDx("プレイヤーモデルの読み込み失敗\n");
        return;
    }

    position = Vec3(-116.0f, 1018.0f, -240.0f);

    MV1SetScale(Player_handle, VGet(12, 12, 12));
    MV1SetPosition(Player_handle, VGet(position.x, position.y, position.z));
}

void Player::Update(float dt)
{
    HandleInput(dt);
    ApplyGravity(dt);

    Vec3 nextPos = position + velocity * dt;

    CollisionWithFloor(nextPos);

    position = nextPos;
    MV1SetPosition(Player_handle, VGet(position.x, position.y, position.z));
}

void Player::Draw()
{
    if (Player_handle != -1)
    {
        MV1DrawModel(Player_handle);
    }
}

/*
    ★ カメラ向き基準の移動処理
*/
void Player::HandleInput(float)
{
    if (!camera) return;

    Vec3 input{ 0,0,0 };

    if (CheckHitKey(KEY_INPUT_W)) input.z += 1;
    if (CheckHitKey(KEY_INPUT_S)) input.z -= 1;
    if (CheckHitKey(KEY_INPUT_A)) input.x -= 1;
    if (CheckHitKey(KEY_INPUT_D)) input.x += 1;

    // 入力なし
    if (input.x == 0 && input.z == 0)
    {
        velocity.x = 0.0f;
        velocity.z = 0.0f;
        return;
    }

    float yaw = camera->GetYaw();

    // カメラ前方向
    Vec3 forward{
        sinf(yaw),
        0.0f,
        cosf(yaw)
    };

    // カメラ右方向
    Vec3 right{
        cosf(yaw),
        0.0f,
        -sinf(yaw)
    };

    Vec3 moveDir =
        forward * input.z +
        right * input.x;

    // 正規化（斜め移動対策）
    float len = sqrtf(moveDir.x * moveDir.x + moveDir.z * moveDir.z);
    if (len > 0.0f)
    {
        moveDir.x /= len;
        moveDir.z /= len;
    }

    velocity.x = moveDir.x * moveSpeed;
    velocity.z = moveDir.z * moveSpeed;
}

void Player::ApplyGravity(float dt)
{
    if (!isGrounded)
    {
        velocity.y += GRAVITY * dt;
    }
}

/*
    ★ 床判定（下向きレイ1本）
*/
void Player::CollisionWithFloor(Vec3& nextPos)
{
    // 上昇中は床判定しない
    if (velocity.y > 0.0f) return;

    isGrounded = false;
    if (!stage) return;

    int stageHandle = stage->GetModelHandle();

    VECTOR start = VGet(
        nextPos.x,
        position.y,
        nextPos.z
    );

    VECTOR end = VGet(
        nextPos.x,
        nextPos.y - radius - 5.0f,
        nextPos.z
    );

    MV1_COLL_RESULT_POLY hit =
        MV1CollCheck_Line(stageHandle, -1, start, end);

    float hitDist = start.y - hit.HitPosition.y;

    if (hit.HitPosition.y > -100000.0f &&
        hitDist >= 0.0f &&
        hitDist <= 20.0f)
    {
        nextPos.y = hit.HitPosition.y + radius;
        velocity.y = 0.0f;
        isGrounded = true;
    }
}
