#pragma once
#include <list>
#include <vector>

enum class SCENE;
class ObjectBase;

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
    /*更新*/
    void Update();
    /*最終更新*/
    void Lastpdate();
    /*描画*/
    void Draw();

    /*リストにオブジェクトを追加する*/
    int Add(ObjectBase* object, int typeNumber);
    /*リストからオブジェクトを除外する*/
    void Delete(unsigned int id, int typeNumber);

    /*オブジェクト全削除*/
    void DeleteAll();
    /*必要であればオブジェクト削除を行う*/
    void DeleteAllIfNeeded();

    /*当たり判定確認*/
    //CollisionData CheckObjectHit(CollisionData collisionData, int typeNumber);

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
    ObjectBase* FindByTag(int tag, int typeNumber = 0, bool inactiveFlag = false, bool deleteGetFlag = false);
    /*タグから複数オブジェクトを取得(vector)*/
    std::vector<ObjectBase*> FindsByTag_vector(int tag, int typeNumber = 0, bool inactiveFlag = false, bool deleteGetFlag = false);
    /*タグから複数オブジェクトを取得(list)*/
    std::list<ObjectBase*> FindsByTag_list(int tag, int typeNumber = 0, bool inactiveFlag = false, bool deleteGetFlag = false);

    /*----------*/
    /*【タイプ】*/
    /*----------*/

    /*指定タイプリストの先頭オブジェクトを取得*/
    ObjectBase* GetTypeObject(int typeNumber);
    /*指定タイプを全取得(vector)*/
    std::vector<ObjectBase*> FindsByType_vector(int typeNumber, bool inactiveFlag = false, bool deleteGetFlag = false);
    /*指定タイプを全取得(list)*/
    std::list<ObjectBase*> FindsByType_list(int typeNumber, bool inactiveFlag = false, bool deleteGetFlag = false);

    /*----------*/
    /*【チーム】*/
    /*----------*/

    /*チームからオブジェクトを取得*/
    ObjectBase* FindByTeam(int team, int typeNumber = 0, bool inactiveFlag = false, bool deleteGetFlag = false);
    /*チームから複数オブジェクト取得(vector)*/
    std::vector<ObjectBase*> FindsByTeam_vector(int team, int typeNumber = 0, bool inactiveFlag = false, bool deleteGetFlag = false);
    /*チームから複数オブジェクト取得(list)*/
    std::list<ObjectBase*> FindsByTeam_list(int team, int typeNumber = 0, bool inactiveFlag = false, bool deleteGetFlag = false);

    /*------------------*/
    /*     【設定】     */
    /*------------------*/

    /*--------*/
    /*【削除】*/
    /*--------*/

    /*指定タグのオブジェクト削除フラグを有効化*/
    void DeleteSetTag(int tag);
    /*指定チームのオブジェクト削除フラグを有効化*/
    void DeleteSetTeam(int team);
    /*指定シーンで生成されたオブジェクトの削除フラグ有効化*/
    void DeleteSetScene(SCENE targetScene);

    /*----------*/
    /*【非有効】*/
    /*----------*/

    /*指定タグのオブジェクトを非有効化*/
    void InactiveSetTag(int tag);
    /*指定チームのオブジェクト削除フラグを非有効化*/
    void InactiveSetTeam(int team);
    /*指定シーンで生成されたオブジェクトを非有効化する*/
    void InactiveSetScene(SCENE targetScene);

private:
    /*----------------*/
    /*【オブジェクト】*/
    /*----------------*/
    
    /*リストの先頭オブジェクトを設定*/
    void SetTypeObject(int typeNumber, ObjectBase* setObject);
};