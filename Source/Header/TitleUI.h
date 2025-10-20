#pragma once
#include "ObjectBases.h"

class TitleUI : public UIBase
{
private:

public:
    TitleUI();
    ~TitleUI();

private:
    /*UI初期化*/
    void UIInitilize();
    /*UI終了*/
    void UIFinalize();
    /*UI更新*/
    void UIUpdate();
    /*UI最終更新*/
    void UILastUpdate();
    /*UI描画*/
    void UIDraw();

    /*選択決定時処理*/
    void DecisionProcess();
};