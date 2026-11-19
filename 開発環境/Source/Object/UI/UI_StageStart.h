#pragma once
#include "TimeData.h"

#include "ObjectBases.h"

class UI_StageStart : public UIBase
{
private:
    // カメラID
    int mnCameraID;

    // 生存時間
    TIME_DATA mstSurvivalTime;

    // フェードイン時間
    const int FADE_IN_TIME = 17 * 25;

    // 生存時間
    const int SURVIVAL_TIME = (17 * 230) + FADE_IN_TIME;

    // フェードインフラグ
    bool mbFadeInFlag;

public:
    UI_StageStart();
    ~UI_StageStart();

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
    
    /*削除処理*/
    void CloceProcess() override;
};