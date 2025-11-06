#pragma once

#include "ObjectBases.h"

class ResultUI : public UIBase
{
private:
    // ラインサイズ
    float mnLineAeraSize;
    // ライン数
    int mnLineNum;

public:
    ResultUI();
    ~ResultUI();

private:
    /*UI初期化*/
    void UIInitilize() override;
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