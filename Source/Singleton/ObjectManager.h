#pragma once
#include <list>
#include <string>
#include <vector>

#include "ObjectBases.h"

enum class SCENE;

class ObjectManager
{
private:
    // 線形リストの先頭アドレス(オブジェクトべース)
    ObjectBase* mpObjectBase;

    // 線形リストの先頭アドレス(キャラクターべース)
    ObjectBase* mpCharacterBase;
    // 線形リストの先頭アドレス(建物べース)
    ObjectBase* mpBuildingBase;
    // 線形リストの先頭アドレス(攻撃べース)
    ObjectBase* mpAttackBase;
    // 線形リストの先頭アドレス(UIべース)
    ObjectBase* mpUIBase;

    // 設定用ID
    unsigned int munSetID;

public:
    /*コンストラクタ*/
    ObjectManager();
    /*デストラクタ*/
    ~ObjectManager();

    /*------------------*/
    /*     【処理】     */
    /*------------------*/

    /*初期化*/
    void Initilize();
    /*終了*/
    void Finalize();

    /// <summary>オブジェクトシーン最終初期化</summary>
    void ObjectSceneLastInitilize();
    /*オブジェクト更新*/
    void ObjectUpdate();
    /*オブジェクト最終更新*/
    void ObjectLastUpdate();
    /*オブジェクト描画*/
    void ObjectDraw();


    /*リストにオブジェクトを追加する*/
    int Add(ObjectBase* object, OBJECT_TYPE typeNumber);
    /*リストからオブジェクトを除外する*/
    void Delete(unsigned int id, OBJECT_TYPE typeNumber);

    /*オブジェクト全削除*/
    void DeleteAll();
    /*必要であればオブジェクト削除を行う*/
    void DeleteAllIfNeeded();

    /*当たり判定確認*/
    //CollisionData CheckObjectHit(CollisionData collisionData, OBJECT_TYPE typeNumber);

    /*------------------*/
    /*     【取得】     */
    /*------------------*/

    /*------*/
    /*【ID】*/
    /*------*/

    /*IDからオブジェクトを取得*/
    ObjectBase* FindByID(int id, bool deleteGetFlag = false);

    /*--------*/
    /*【タグ】*/
    /*--------*/

    /*タグからオブジェクトを取得*/
    ObjectBase* FindByTag(std::string tag, OBJECT_TYPE typeNumber = OBJECT_TYPE::BASE, bool inactiveFlag = false, bool deleteGetFlag = false);
    /*タグから複数オブジェクトを取得(vector)*/
    std::vector<ObjectBase*> FindsByTag_vector(std::string tag, OBJECT_TYPE typeNumber = OBJECT_TYPE::BASE, bool inactiveFlag = false, bool deleteGetFlag = false);
    /*タグから複数オブジェクトを取得(list)*/
    std::list<ObjectBase*> FindsByTag_list(std::string tag, OBJECT_TYPE typeNumber = OBJECT_TYPE::BASE, bool inactiveFlag = false, bool deleteGetFlag = false);

    /*----------*/
    /*【タイプ】*/
    /*----------*/

    /*指定タイプリストの先頭オブジェクトを取得*/
    ObjectBase* GetTypeObject(OBJECT_TYPE typeNumber);
    /*指定タイプを全取得(vector)*/
    std::vector<ObjectBase*> FindsByType_vector(OBJECT_TYPE typeNumber, bool inactiveFlag = false, bool deleteGetFlag = false);
    /*指定タイプを全取得(list)*/
    std::list<ObjectBase*> FindsByType_list(OBJECT_TYPE typeNumber, bool inactiveFlag = false, bool deleteGetFlag = false);
    
    /*全キャラクターベース取得*/
    std::vector <CharacterBase*> FindsByType_Character(bool inactiveFlag = false, bool deleteGetFlag = false);
    /*全ビルディングベース取得*/
    std::vector <BuildingBase*> FindsByType_Building(bool inactiveFlag = false, bool deleteGetFlag = false);
    /*全アタックベース取得*/
    std::vector <AttackBase*> FindsByType_Attack(bool inactiveFlag = false, bool deleteGetFlag = false);

    /*----------*/
    /*【チーム】*/
    /*----------*/

    /*チームからオブジェクトを取得*/
    ObjectBase* FindByTeam(int team, OBJECT_TYPE typeNumber = OBJECT_TYPE::BASE, bool inactiveFlag = false, bool deleteGetFlag = false);
    /*チームから複数オブジェクト取得(vector)*/
    std::vector<ObjectBase*> FindsByTeam_vector(int team, OBJECT_TYPE typeNumber = OBJECT_TYPE::BASE, bool inactiveFlag = false, bool deleteGetFlag = false);
    /*チームから複数オブジェクト取得(list)*/
    std::list<ObjectBase*> FindsByTeam_list(int team, OBJECT_TYPE typeNumber = OBJECT_TYPE::BASE, bool inactiveFlag = false, bool deleteGetFlag = false);

    /*------------------*/
    /*     【設定】     */
    /*------------------*/

    /*--------*/
    /*【削除】*/
    /*--------*/

    /*指定タグのオブジェクト削除フラグを有効化*/
    void DeleteSetTag(std::string tag);
    /*指定チームのオブジェクト削除フラグを有効化*/
    void DeleteSetTeam(int team);
    /*指定シーンで生成されたオブジェクトの削除フラグ有効化*/
    void DeleteSetScene(SCENE targetScene);

    /*----------*/
    /*【非有効】*/
    /*----------*/

    /*指定タグのオブジェクトを非有効化*/
    void InactiveSetTag(std::string tag);
    /*指定チームのオブジェクト削除フラグを非有効化*/
    void InactiveSetTeam(int team);
    /*指定シーンで生成されたオブジェクトを非有効化する*/
    void InactiveSetScene(SCENE targetScene);

private:
    /*----------------*/
    /*【オブジェクト】*/
    /*----------------*/
    
    /*リストの先頭オブジェクトを設定*/
    void SetTypeObject(OBJECT_TYPE typeNumber, ObjectBase* setObject);
};