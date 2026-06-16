#pragma once
#include "ObjectBase.h"

/*--------------------------------------------------------*/
/*               【ビルディングベース関係】               */
/*--------------------------------------------------------*/

/*------------------------------------------*/
/*          【ビルディングベース】          */
/*------------------------------------------*/
class BuildingBase : public ObjectBase
{
public:
    enum class BUILDING_OBJECT_BIT_FLAG_NUBER
    {
        BUILDING_OBJECT_BIT_MAX = ObjectBase::OBJECT_BIT_FLAG_NUBER::OBJECT_BIT_MAX
    };

protected:
    // ポジション
    VECTOR mvPosition;

    // モデルベース

    //fsm

    /*当たり判定用 多分モデルでいける*/
//    CollisionData HitCheck(CollisionData collisionData) override { return CollisionCheck(collisionData); }

public:
    BuildingBase(bool nextSceneDeleteFlag);
    ~BuildingBase();

    /*初期化*/
    void Initilize() override final;
    /// <summary>シーン最終初期化</summary>
    void SceneLastInitilize() override final;
    /*終了*/
    void Finalize() override final;
    /*更新*/
    void Update() override final;
    /*最終更新*/
    void LastUpdate() override final;
    /*描画*/
    void Draw() override final;

    /*----------------------*/
    /*     【独自処理】     */
    /*----------------------*/

protected:
    /*ビルディング初期化*/
    virtual void BuildingInitilize() = 0;
    /*ビルディングシーン最終初期化*/
    virtual void BuildingSceneLastInitilize() = 0;
    /*ビルディング終了*/
    virtual void BuildingFinalize() = 0;
    /*ビルディング更新*/
    virtual void BuildingUpdate() = 0;
    /*ビルディング最終更新*/
    virtual void BuildingLastUpdate() = 0;
    /*ビルディング描画*/
    virtual void BuildingDraw() = 0;
};