#pragma once
#include <string>
#include <vector>

#include "TelopData.h"
#include "TimeData.h"

class TelopManager
{
private:
    // TODO: 数字で扱うようにする
    // テロップ文字列
    std::vector<std::string> msTelopStrings;

    // 最終テロップ描画時間
    TIME_DATA mstPreTelopDrawTime;

    static constexpr int TELOP_TIME = 1700;

public:
    TelopManager();
    ~TelopManager();
    
    /// <summary>終了</summary>
    void Finalize();
    
    /// <summary>更新</summary>
    void Update();
    
    /// <summary>描画</summary>
    void Draw();

    /// <summary>テロップ描画</summary>
    void DrawTelop(TELOP_DATA& telopData);

    /// <summary>テロップ追加</summary>
    void AddTelop(std::string telop);

private:
    /// <summary>テロップ削除</summary>
    void DeleteTelop();

    /// <summary>3Dポジションテロップ描画</summary>
    void DrawTelop_Position3D(TELOP_DATA& telopData);
};