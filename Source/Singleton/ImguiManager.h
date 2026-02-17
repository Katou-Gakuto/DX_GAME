#pragma once

class ImguiManager
{
private:
    // テスト用
    int mpMode;

public:

    enum FLOAT_TYPE
    {

    };

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

    /// <summary>floatのimgui</summary>
    void FloatImgui();
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