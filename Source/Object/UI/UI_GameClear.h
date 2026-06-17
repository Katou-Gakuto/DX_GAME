#pragma once

#include "ObjectBase_UI.h"

class UI_GameClear : public UIBase
{
public:
    UI_GameClear();
    ~UI_GameClear();

private:
    /*UI初期化*/
    void UIInitilize() override;
    /*UIシーン最終初期化*/
    void UISceneLastInitilize() override;
    /*UI終了*/
    void UIFinalize() override;
    /*UI更新*/
    void UIUpdate() override;
    /*UI最終更新*/
    void UILastUpdate() override;
    /*UI描画*/
    void UIDraw() override;

    /*選択決定時処理*/
    void DecisionProcess() override;
};