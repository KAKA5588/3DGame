#pragma once
class Stage
{
public:
    Stage();
    ~Stage();

    void Initialize();
    void Update();
    void Draw();

    // ★ プレイヤーから取得するために必要
    int GetModelHandle() const { return Stage_handle; }

private:
    int Stage_handle = -1;
};
