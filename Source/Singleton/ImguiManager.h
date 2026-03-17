#pragma once
#include <string>
#include <vector>

#include "ImguiData.h"

// TODO: 最終的にはプロジェクトから外す

class ImguiManager
{
private:
    // テスト用
    int mpMode;

    // IMGUIデータ float
    std::vector<IMGUI_FLOAT_DATA> mstImguiFloatDatas;

    // IMGUIデータ int
    std::vector<IMGUI_INT_DATA> mstImguiIntDatas;

    // 追加Imguiナンバー
    int mnAddNumber;

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

    /// <summary>floatのImgui情報設定</summary>
    std::string SetFloatImgui(IMGUI_FLOAT_DATA imguiFloatData);

    /// <summary>intのImgui情報設定</summary>
    std::string SetIntImgui(IMGUI_INT_DATA imguiIntData);

    /// <summary>Imgui情報削除</summary>
    void DeleteImguiData(std::string labelName);

    /// <summary>Imgui追加描画</summary>
    void AddDrawImgui(IMGUI_FLOAT_DATA imguiFloatData);
    /// <summary>Imgui追加描画</summary>
    void AddDrawImgui(IMGUI_INT_DATA imguiIntData);

private:
    /*floatのImguui描画*/
    void DrawFloatImgui(IMGUI_FLOAT_DATA imguiFloatData);

    /*intのImguui描画*/
    void DrawIntImgui(IMGUI_INT_DATA imguiIntData);
};
/*
構造体作成
const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags
const char* label, float v[2], float v_min, float v_max, const char* format, ImGuiSliderFlags flags
const char* label, float v[3], float v_min, float v_max, const char* format, ImGuiSliderFlags flags
const char* label, float v[4], float v_min, float v_max, const char* format, ImGuiSliderFlags flags
const char* label, float* v_rad, float v_degrees_min, float v_degrees_max, const char* format, ImGuiSliderFlags flags
const char* label, float* v, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags
*/