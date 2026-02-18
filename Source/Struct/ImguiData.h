#pragma once
#include <string>
#include <vector>

#include "ImguiEnum.h"

#include "imgui.h"

template<typename VariableType>
struct IMGUI_TEMPLATE_DATA
{
public:
#if _DEBUG
    std::vector<VariableType*> VariableDatas = {};    // 変数ポインタ

    float Speed = 1.0f; // ドラッグ時の変化速度

    float Step = 0.0f;      // 刻み幅
    float StepFast = 0.0f;  // Ctrl押しながらの刻み幅

    float Min = 0;  // 最小値
    float Max = 0;  // 最大値
    
    std::string Label = "NONE";  // ラベル
    std::string Format = "%.3f"; // 表示数字

    ImGuiSliderFlags Flag = 0;  // オプションフラグ

    IMGUI_TYPE ImguiType = IMGUI_TYPE::SLIDER1; // Imgui種類

#endif
    /*------------*/
    /*【リセット】*/
    /*------------*/
    /// <summary>変数リセット</summary>
    void ReSetVariable()
    {
    #if _DEBUG
        VariableDatas.clear();
    #endif
    }

    /*--------*/
    /*【設定】*/
    /*--------*/
    /// <summary>変数設定</summary>
    void SetVariable(VariableType *src) {
    #if _DEBUG
        VariableDatas.push_back(src);
    #endif
    }

    /// <summary>速度設定</summary>
    void SetSpeed(float speed) {
    #if _DEBUG
        Speed = speed;
    #endif
    }

    /// <summary>刻み幅設定</summary>
    void SetStep(float step) {
    #if _DEBUG
        Step = step;
    #endif
    }
    /// <summary>刻み幅(ctrl)設定</summary>
    void SetStepFast(float stepFast) {
    #if _DEBUG
        StepFast = stepFast;
    #endif
    }

    /// <summary>最低値設定</summary>
    void SetMin(float min) {
    #if _DEBUG
        Min = min;
    #endif
    }
    /// <summary>最大値設定</summary>
    void SetMax(float max) {
    #if _DEBUG
        Max = max;
    #endif
    }

    /// <summary>ラベル設定</summary>
    void SetLabel(std::string label) {
    #if _DEBUG
        Label = label;
    #endif
    }
    /// <summary>フォーマット設定</summary>
    void SetFormat(std::string format) {
    #if _DEBUG
        Format = format;
    #endif
    }

    /// <summary>オプションフラグ設定</summary>
    void SetFlag(ImGuiSliderFlags flag) {
    #if _DEBUG
        Flag = flag;
    #endif
    }

    /// <summary>Imgui種類設定</summary>
    void SetImguiType(IMGUI_TYPE imguiType) {
    #if _DEBUG
        ImguiType = imguiType;
    #endif
    }
};

// float
struct IMGUI_FLOAT_DATA : public IMGUI_TEMPLATE_DATA<float>
{
};

// int
struct IMGUI_INT_DATA : public IMGUI_TEMPLATE_DATA<float>
{
};