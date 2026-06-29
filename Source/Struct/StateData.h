#pragma once
struct OneAnimationData;
struct AnimationDatas;
struct CameraData;

class Animation;
class CameraManager;

// ステート変更条件情報
template<typename stateNumber, typename conditionData>
struct STATE_CHANGE_CRITERIA_DATA
{
    stateNumber ChangeNumber;    // 変更ステートナンバー
    bool(*ChangeFlag)(conditionData* changeConditionData);   // 変更フラグ用関数

    STATE_CHANGE_CRITERIA_DATA() = default;

    STATE_CHANGE_CRITERIA_DATA(stateNumber changeNumber, bool (*changeFlag)(conditionData*))
    : ChangeNumber(changeNumber)
    , ChangeFlag(changeFlag)
    {
    }
};

struct STATE_ANEMATION_DATA
{
    // Animation* StateAnimation;
    // OneAnimationData* StateOneAnimationData;
    // AnimationDatas* StateAnimationDatas;
    // int nextState;
    Animation* animation;   // アニメーションクラス
    OneAnimationData* nowAnimationData; // アニメーション情報
    OneAnimationData* preAnimationData; // 前のアニメーション情報
    int nextState;  // FSMで設定
};