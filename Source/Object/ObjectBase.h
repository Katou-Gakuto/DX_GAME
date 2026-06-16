#pragma once
#include <list>
#include <string>
#include <map>
#include <vector>

#include "AttackData.h"
#include "BitFlag.h"
#include "CollisionData.h"
#include "DrawData.h"
#include "Status.h"
#include "TimeData.h"
#include "ResourceData.h"// TODO: 消す

#include "DxLib.h"

#include "AnimationBase.h"
#include "KeyState.h"
#include "ModelsControllerBase.h"
#include "ResourceManager.h"
#include "TimeManager.h"

enum class ATTACK_METHOD_TYPE;
enum class LOAD_ANIMATION_DATA_FACTORY_NUMBER;
enum class MODEL_TYPE;
enum class SCENE;

class AttackBase;
class FSMAnimation;
class FSMCharacter;
class FSMUI;

class ObjectBase;
#ifdef _DEBUG
bool DEBUG_OBJECT_POINT_CHECK(void* p, bool check = false);
#endif

/*--------------------------------------------------------*/
/*               【オブジェクトベース関連】               */
/*--------------------------------------------------------*/

/*------------------------------------------------*/
/*          【オブジェクトベース用enum】          */
/*------------------------------------------------*/
;
// オブジェクトタイプ
enum class OBJECT_TYPE
{
    BASE = 0,
    CHARACTER_BASE,
    BUILDING_BASE,
    ATTACK_BASE,
    UI_BASE
};

/*------------------------------------------*/
/*          【オブジェクトベース】          */
/*------------------------------------------*/

class ObjectBase
{
public:
    enum class OBJECT_BIT_FLAG_NUBER
    {
        OBJECT_BIT_MAX = 0
    };

private:
    // 前オブジェクトへのポインタ
    ObjectBase* mpPrevObject;
    // 次オブジェクトへのポインタ
    ObjectBase* mpNextObject;

    // 継承したクラスと同タイプの前オブジェクトへのポインタ
    ObjectBase* mpInheritClassPrevObject;
    // 継承したクラスと同タイプの次オブジェクトへのポインタ
    ObjectBase* mpInheritClassNextObject;

    // 削除フラグ
    bool mbIsDeleteFlag;
    // 有効フラグ
    bool mbIsActiveFlag;

    // 次のシーン削除するフラグ
    bool mbNextSceneDeleteFlag;

    // 識別タグ
    std::string mnTag;
    // チーム
    int mnTeam;
    // 個別ナンバー
    unsigned int munID;

    // オブジェクトの種類
    OBJECT_TYPE meObjectType;

protected:
    // 生成されたシーン
    SCENE meObjectScene;

    // フラグ
    BIT_FLAG<unsigned long long> mullFlags;

public:

    /*コンストラクタ*/
    ObjectBase(OBJECT_TYPE objectType, bool isActiveFlag, bool nextSceneDeleteFlag);
    /*デストラクタ*/
    ~ObjectBase();

    /*初期化*/
    virtual void Initilize() = 0;
    /// <summary>シーン最終初期化</summary>
    virtual void SceneLastInitilize() = 0;
    /*終了*/
    virtual void Finalize() = 0;
    /*更新*/
    virtual void Update() = 0;
    /*最終更新*/
    virtual void LastUpdate() = 0;
    /*描画*/

    virtual void Draw() = 0;
#ifdef _DEBUG
    /*前オブジェクトへのポインタ取得*/
    inline ObjectBase* GetPrevObject(bool allBaseFlag = true) {

        if (DEBUG_OBJECT_POINT_CHECK(allBaseFlag ? mpPrevObject : mpInheritClassPrevObject))
        {
            if (allBaseFlag)
            {
                mpPrevObject = reinterpret_cast<ObjectBase*>(reinterpret_cast<uintptr_t>(mpPrevObject) | (reinterpret_cast<uintptr_t>(mpInheritClassPrevObject) & 0xffff'ffff'0000'0000u));
            }
            else
            {
                mpInheritClassPrevObject = reinterpret_cast<ObjectBase*>(reinterpret_cast<uintptr_t>(mpInheritClassPrevObject) | (reinterpret_cast<uintptr_t>(mpPrevObject) & 0xffff'ffff'0000'0000u));
            }
        }

   

        return allBaseFlag ? mpPrevObject : mpInheritClassPrevObject;
    }
    /*次オブジェクトへのポインタ取得*/
    inline ObjectBase* GetNextObject(bool allBaseFlag = true) {

        if (DEBUG_OBJECT_POINT_CHECK(allBaseFlag ? mpNextObject : mpInheritClassNextObject))
        {
            if (allBaseFlag)
            {
                mpNextObject = reinterpret_cast<ObjectBase*>(reinterpret_cast<uintptr_t>(mpNextObject) | (reinterpret_cast<uintptr_t>(mpInheritClassNextObject) & 0xffff'ffff'0000'0000u));
            }
            else
            {
                mpInheritClassNextObject = reinterpret_cast<ObjectBase*>(reinterpret_cast<uintptr_t>(mpInheritClassNextObject) | (reinterpret_cast<uintptr_t>(mpNextObject) & 0xffff'ffff'0000'0000u));
            }
        }


        return allBaseFlag ? mpNextObject : mpInheritClassNextObject;
    }
    /*前オブジェクトのポインタを設定する*/
    inline void SetPrevObject(ObjectBase* object, bool allBaseFlag = true) { DEBUG_OBJECT_POINT_CHECK(object, true); if (allBaseFlag) { mpPrevObject = object; } else { mpInheritClassPrevObject = object; } }
    /*次オブジェクトのポインタを設定する*/
    inline void SetNextObject(ObjectBase* object, bool allBaseFlag = true) { DEBUG_OBJECT_POINT_CHECK(object, true); if (allBaseFlag) { mpNextObject = object; } else { mpInheritClassNextObject = object; } }

#else
    /*前オブジェクトへのポインタ取得*/
    inline ObjectBase* GetPrevObject(bool allBaseFlag = true) { return allBaseFlag ? mpPrevObject : mpInheritClassPrevObject; }
    /*次オブジェクトへのポインタ取得*/
    inline ObjectBase* GetNextObject(bool allBaseFlag = true) { return allBaseFlag ? mpNextObject : mpInheritClassNextObject; }

    /*前オブジェクトのポインタを設定する*/
    inline void SetPrevObject(ObjectBase* object, bool allBaseFlag = true) { if (allBaseFlag) { mpPrevObject = object; } else { mpInheritClassPrevObject = object; } }
    /*次オブジェクトのポインタを設定する*/
    inline void SetNextObject(ObjectBase* object, bool allBaseFlag = true) { if (allBaseFlag) { mpNextObject = object; } else { mpInheritClassNextObject = object; } }

#endif
    /*削除フラグ設定(true = 削除)*/
    inline void SetDeleteFlag(const bool flag) { mbIsDeleteFlag = flag; }
    /*削除フラグ取得*/
    inline bool IsDeleteFlag() const { return mbIsDeleteFlag; }

    /*有効フラグ設定*/
    inline void SetActiveFlag(const bool flag) { mbIsActiveFlag = flag; }
    /*有効フラグ取得*/
    inline bool IsActiveFlag() const { return mbIsActiveFlag; }

    /*タグ設定*/
    inline void SetTag(const std::string& tag) { mnTag = tag; }
    /*タグ取得*/
    inline std::string GetTag() const { return mnTag; }

    /*チーム設定*/
    inline void SetTeam(const int team) { mnTeam = team; }
    /*チーム取得*/
    inline int GetTeam() const { return mnTeam; }

    /*個別ナンバー取得*/
    inline unsigned int GetID() const { return munID; }

    /*次のシーン削除するフラグを設定*/
    inline void SetNextSceneDeleteFlag(bool nextSceneDeleteFlag) { mbNextSceneDeleteFlag = nextSceneDeleteFlag; }
    /*次のシーン削除するフラグを取得*/
    inline bool GetNextSceneDeleteFlag() const { return mbNextSceneDeleteFlag; }

    /*オブジェクト種類(ナンバー)取得*/
    inline OBJECT_TYPE GetObjectTypeNumber() const { return meObjectType; }

    /*オブジェクトのシーンを取得*/
    inline SCENE GetObjectScene() const { return meObjectScene; }
    /*オブジェクトのシーン設定*/
    inline void SetObjectScene(SCENE objectScene) { meObjectScene = objectScene; }

    inline BIT_FLAG<unsigned long long> GetObjectBitFlag() const { return mullFlags; }

    /*--------------------------*/
    /*【継承処理キャスト省略用】*/
    /*--------------------------*/
    /*当たり判定*/
    virtual void HitCheck(CollisionData& collisionData) {};
};