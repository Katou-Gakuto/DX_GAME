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
    static constexpr int IMGUI_VARIABLE_MAX = 4;

    std::vector<VariableType*> VariableDatas = {};    // 変数ポインタ

    VariableType PreVariable[IMGUI_VARIABLE_MAX];    // 前の変数

    VariableType ChangeVariable[IMGUI_VARIABLE_MAX]; // 変更用変数

    float Speed = 1.0f; // ドラッグ時の変化速度

    float Step = 0.0f;      // 刻み幅
    float StepFast = 0.0f;  // Ctrl押しながらの刻み幅

    VariableType Min = 0.0f;  // 最小値
    VariableType Max = 0.0f;  // 最大値
    
    std::string Label = "NONE";  // ラベル
    std::string Format = "%.6f"; // 表示数字

    ImGuiSliderFlags Flag = 0;  // オプションフラグ

    IMGUI_TYPE ImguiType = IMGUI_TYPE::SLIDER1; // Imgui種類

#endif
    IMGUI_TEMPLATE_DATA()
#if _DEBUG
    : Speed(1.0f)
    , Step(0.0f)
    , StepFast(0.0f)
    , Min((VariableType)0)
    , Max((VariableType)0)
    , Label("NONE")
    , Format("%.6f")
    , Flag(0)
    , ImguiType(IMGUI_TYPE::SLIDER1)
#endif
    {
#if _DEBUG
        VariableDatas.clear();
#endif
    }

    IMGUI_TEMPLATE_DATA(
                        std::vector<VariableType*> variableDatas,
                        VariableType* preVariable,
                        VariableType* changeVariable,
                        float speed = 1.0f,
                        float step = 0.0f,
                        float stepFast = 0.0f,
                        VariableType min = (VariableType)0,
                        VariableType max = (VariableType)0,
                        std::string label = "NONE",
                        std::string format = "%.6f",
                        ImGuiSliderFlags flag = 0,
                        IMGUI_TYPE imguiType = IMGUI_TYPE::SLIDER1
                        )
#if _DEBUG
    : Speed(speed)
    , Step(step)
    , StepFast(stepFast)
    , Min(min)
    , Max(max)
    , Label(label)
    , Format(format)
    , Flag(flag)
    , ImguiType(imguiType)
    , VariableDatas(variableDatas)
#endif
    {
#if _DEBUG
        for (int i = 0; i < IMGUI_VARIABLE_MAX; i++)
        {
            PreVariable[i] = preVariable[i];
            ChangeVariable[i] = changeVariable[i];
        }
#endif
    }

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
    void AddVariable(VariableType *src) {
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
    void SetMin(VariableType min) {
    #if _DEBUG
        Min = min;
    #endif
    }
    /// <summary>最大値設定</summary>
    void SetMax(VariableType max) {
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
struct IMGUI_INT_DATA : public IMGUI_TEMPLATE_DATA<int>
{
};