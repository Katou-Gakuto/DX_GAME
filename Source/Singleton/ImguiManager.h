#pragma once

class ImguiManager
{
private:
    // テスト用
    int mpMode;

public:
    ImguiManager();
    ~ImguiManager();

    
    void DxInit();

    /// <summary>初期化</summary>
    void Initilize();
    /// <summary>終了</summary>
    void Finalize();

    /// <summary>更新</summary>
    void Update();
    /// <summary>描画</summary>
    void Draw();

    /// <summary>floatスライダー</summary>

    /// <summary>floatDrag?</summary>
};