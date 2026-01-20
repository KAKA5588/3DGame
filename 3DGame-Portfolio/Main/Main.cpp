#include "DxLib.h"
#include "../Player/Player.h"

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    // DxLib初期化
    if (DxLib_Init() == -1)
    {
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);
    // ゲームオブジェクト生成
    Player player;
    player.Initialize();

    // 仮の初期位置
    player.position = { 0.0f, 0.0f, 0.0f };

  
    // メインループ
  
    while (ProcessMessage() == 0)
    {
        ClearDrawScreen();

        float deltaTime = 1.0f / 60.0f; // 仮固定フレーム
     
        player.Update(deltaTime);

        player.Draw();

        // 画面反映
        ScreenFlip();
    }

    // DxLib終了
    DxLib_End();
    return 0;
}
