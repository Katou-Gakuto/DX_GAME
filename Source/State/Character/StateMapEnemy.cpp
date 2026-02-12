#include "GameDatas.h"

#include "Master.h"

#include "DataManager.h"
#include "GameManager.h"
#include "KeyState.h"
#include "StateMapEnemy.h"
#include "SceneManager.h"
#include "TargetManager.h"
#include "UtilCalc.h"
#include "UtilChange.h"

/*------------------*/
/*     【共通】     */
/*------------------*/

/*----------------------------*/
/*【マップエネミー共通処理用】*/
/*----------------------------*/
MapEnemyProcess::MapEnemyProcess(SCENE mapScene)
: mpKeyState(Master::mpKeyState)
, mpSceneManager(Master::mpGameManager->GetSceneManager())
, mpTargetManager(Master::mpGameManager->GetTargetManager())
, meMapScene(mapScene)
{
}

// 一定範囲内にプレイヤーターゲットがいるなら「true」
bool MapEnemyProcess::PlayerTargetCheck(CharacterBase* character, float range)
{
    return UtilCalc::SphereCollision(character->GetPos(), range, mpTargetManager->GetTarget(TARGET_TYPE::PLAYER).target->GetPos(), 180.0f);
}

// 死亡
void MapEnemyProcess::MapEnemyDeath(CharacterBase* character)
{
    mpTargetManager->Delete(character, TARGET_TYPE::ENEMY);
    if ((UtilChange::SceneState(mpSceneManager->GetNowScene()) != SCENE::TOWN) && (mpTargetManager->GetTargets(TARGET_TYPE::ENEMY).size() <= 0))
    {
        mpSceneManager->SetNextScene(Master::mpDataManager->GetPlayPlayerData().townType);
    }
}

// マップシーン移動開始する
void MapEnemyProcess::SetMapScene(CharacterBase* character)
{
    mpSceneManager->SetNextScene(meMapScene);

    // 削除情報に設定
    DELETE_CHARACTER_DATA deleteCharacterData;
    deleteCharacterData.sceneType = mpSceneManager->GetNowScene();
    deleteCharacterData.characterID = character->GetID();
    if (UtilChange::SceneState(mpSceneManager->GetNowScene()) == SCENE::DUNGEON)
    {
        Master::mpDataManager->SetDungeonDeleteCharacterID(deleteCharacterData);
    }
    else
    {
        Master::mpDataManager->SetTownDeleteCharacterID(deleteCharacterData);
    }
}

/*--------------------------*/
/*     【基本ステート】     */ 
/*--------------------------*/

/*----------------------------*/
/*【Idleマップエネミーテート】*/
/*----------------------------*/
IdleMapEnemyState::IdleMapEnemyState(SCENE mapScene)
: IStateCharacter()
, MapEnemyProcess(mapScene)
{
    mStateNumber = (int)MAP_ENEMY_STATE::IDLE_MAP_ENEMY_STATE;
}

// この状態に入った時の処理
void IdleMapEnemyState::OnEnter(CharacterBase* character)
{
    switch (UtilChange::SceneState(mpSceneManager->GetNowScene()))
    {
    case SCENE::TOWN:
        //printfDx("テロップ：ダンジョンへ行けないです\n");
        break;

    case SCENE::DUNGEON:
        //printfDx("テロップ：バトルへ行けないです\n");
        break;
    }
}

// この状態を出る時の処理
void IdleMapEnemyState::OnExit(CharacterBase* character)
{
}

// ステート変更確認
int IdleMapEnemyState::StateCheck(CharacterBase* character)
{
    if (PlayerTargetCheck(character, 300.0f))
    {
        return (int)MAP_ENEMY_STATE::TELOP_MAP_ENEMY_STATE;
    }

    return mStateNumber;
}

// 更新
void IdleMapEnemyState::Update(CharacterBase* character)
{
}

// 最終更新
void IdleMapEnemyState::LastUpdate(CharacterBase* character)
{
}

// 描画
void IdleMapEnemyState::Draw(CharacterBase* character)
{
}

// 死亡
void IdleMapEnemyState::Death(CharacterBase* character)
{
    MapEnemyDeath(character);
}

/*--------------------------------*/
/*【テロップマップエネミーテート】*/
/*--------------------------------*/
TelopMapEnemyState::TelopMapEnemyState(SCENE mapScene)
: IStateCharacter()
, MapEnemyProcess(mapScene)
{
    mStateNumber = (int)MAP_ENEMY_STATE::TELOP_MAP_ENEMY_STATE;
}

// この状態に入った時の処理
void TelopMapEnemyState::OnEnter(CharacterBase* character)
{
    switch (UtilChange::SceneState(mpSceneManager->GetNowScene()))
    {
    case SCENE::TOWN:
        //printfDx("テロップ：ダンジョンへ行くにはEnterキーを押してください\n");
        break;

    case SCENE::DUNGEON:
        //printfDx("テロップ：バトルへ行くにはEnterキーを押してください\n");
        break;
    }
}

// この状態を出る時の処理
void TelopMapEnemyState::OnExit(CharacterBase* character)
{
}

// ステート変更確認
int TelopMapEnemyState::StateCheck(CharacterBase* character)
{
    if (!PlayerTargetCheck(character,300.0f))
    {
        return (int)MAP_ENEMY_STATE::IDLE_MAP_ENEMY_STATE;
    }

    return mStateNumber;
}

// 更新
void TelopMapEnemyState::Update(CharacterBase* character)
{
    if (mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::ENTER))
    {
        SetMapScene(character);
        clsDx();
    }
}

// 最終更新
void TelopMapEnemyState::LastUpdate(CharacterBase* character)
{
}

// 描画
void TelopMapEnemyState::Draw(CharacterBase* character)
{
}

// 死亡
void TelopMapEnemyState::Death(CharacterBase* character)
{
    MapEnemyDeath(character);
}