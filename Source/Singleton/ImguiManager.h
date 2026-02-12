#pragma once

#if _DEBUG
class ImguiManager
{
public:
    ImguiManager();
    ~ImguiManager();

    /// <summary>初期化</summary>
    void Initilize();
    /// <summary>終了</summary>
    void Finalize();

    /// <summary>更新</summary>
    void Update();
    /// <summary>描画</summary>
    void Draw();
};
#endif