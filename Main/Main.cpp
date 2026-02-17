#include "DxLib.h"
#include "../Stage/Stage.h"
#include "../Camera/Camera.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    SetGraphMode(1920, 1080, 32);
    ChangeWindowMode(TRUE);

    if (DxLib_Init() == -1)
    {
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);

    Stage stage;
    stage.Initialize();

    Player player;
    player.Initialize();

    Enemy enemy;
    enemy.Initialize();

    Camera camera;
    camera.Initialize();

    camera.SetTarget(&player);
    player.SetCamera(&camera);
    player.SetStage(&stage);

    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        ClearDrawScreen();

        float dt = 1.0f / 60.0f;

        player.Update(dt);
        camera.Update(dt);
        camera.Apply();

        enemy.Update(dt);
        enemy.Draw();


        player.Draw();

        stage.Update();
        stage.Draw();

        ScreenFlip();
    }

    DxLib_End();
    return 0;
}
