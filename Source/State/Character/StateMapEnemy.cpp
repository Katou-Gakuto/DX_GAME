#include "GameDataEnum.h"
#include "StateEnum.h"
#include "GameDatas.h"

#include "Master.h"

#include "DataManager.h"
#include "EnemyCommonProcessing.h"
#include "GameManager.h"
#include "KeyState.h"
#include "StateMapEnemy.h"
#include "SceneManager.h"
#include "TargetManager.h"
#include "UtilCalc.h"
#include "UtilChange.h"

/*------------------*/
/*     ・ｽy・ｽ・ｽ・ｽﾊ】     */
/*------------------*/

/*----------------------------*/
/*・ｽy・ｽ}・ｽb・ｽv・ｽG・ｽl・ｽ~・ｽ[・ｽ・ｽ・ｽﾊ擾ｿｽ・ｽ・ｽ・ｽp・ｽz*/
/*----------------------------*/
MapEnemyProcess::MapEnemyProcess(SCENE mapScene)
: EnemyCommonProcessing(STATE_ENEMY_TYPE::MAP_ENEMY)
, mpKeyState(Master::mpKeyState)
, mpSceneManager(Master::mpGameManager->GetSceneManager())
, mpTargetManager(Master::mpGameManager->GetTargetManager())
, meMapScene(mapScene)
{
}

// ・ｽ・ｽ・ｽﾍ囲難ｿｽ・ｽﾉプ・ｽ・ｽ・ｽC・ｽ・ｽ・ｽ[・ｽ^・ｽ[・ｽQ・ｽb・ｽg・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾈゑｿｽutrue・ｽv
bool MapEnemyProcess::PlayerTargetCheck(CharacterBase* character, float range)
{
    return UtilCalc::SphereCollision(character->GetPos(), range, mpTargetManager->GetTarget(TARGET_TYPE::PLAYER).target->GetPos(), 180.0f);
}

// ・ｽ・ｽ・ｽS
void MapEnemyProcess::MapEnemyDeath(CharacterBase* character)
{
    mpTargetManager->Delete(character, TARGET_TYPE::ENEMY);
    if ((UtilChange::SceneState(mpSceneManager->GetNowScene()) != SCENE::TOWN) && (mpTargetManager->GetTargets(TARGET_TYPE::ENEMY).size() <= 0))
    {
        mpSceneManager->SetNextScene(Master::mpDataManager->GetPlayPlayerData().sceneData[DATA_SCENE::TOWN].sceneType);
    }
}

// ・ｽ}・ｽb・ｽv・ｽV・ｽ[・ｽ・ｽ・ｽﾚ難ｿｽ・ｽJ・ｽn・ｽ・ｽ・ｽ・ｽ
void MapEnemyProcess::SetMapScene(CharacterBase* character)
{
    mpSceneManager->SetNextScene(meMapScene);

    // ・ｽ尞懶ｿｽ・ｽ・ｽﾉ設抵ｿｽ
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
/*     ・ｽy・ｽ・ｽ{・ｽX・ｽe・ｽ[・ｽg・ｽz     */
/*--------------------------*/

/*----------------------------*/
/*・ｽyIdle・ｽ}・ｽb・ｽv・ｽG・ｽl・ｽ~・ｽ[・ｽe・ｽ[・ｽg・ｽz*/
/*----------------------------*/
IdleMapEnemyState::IdleMapEnemyState(SCENE mapScene, std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
: IStateCharacter(stateChangeCriterias, STATE_TYPE_CHARACTER::IDLE_MAP_ENEMY_STATE, STATE_TYPE_CHARACTER::IDLE_MAP_ENEMY_STATE)
, MapEnemyProcess(mapScene)
{
}

// ・ｽ・ｽ・ｽﾌ擾ｿｽﾔに難ｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾌ擾ｿｽ・ｽ・ｽ
void IdleMapEnemyState::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
	EnemyGraphDataInitialize(character);
    switch (UtilChange::SceneState(mpSceneManager->GetNowScene()))
    {
    case SCENE::TOWN:
        //printfDx("・ｽe・ｽ・ｽ・ｽb・ｽv・ｽF・ｽ_・ｽ・ｽ・ｽW・ｽ・ｽ・ｽ・ｽ・ｽﾖ行・ｽ・ｽ・ｽﾈゑｿｽ・ｽﾅゑｿｽ\n");
        break;

    case SCENE::DUNGEON:
        //printfDx("・ｽe・ｽ・ｽ・ｽb・ｽv・ｽF・ｽo・ｽg・ｽ・ｽ・ｽﾖ行・ｽ・ｽ・ｽﾈゑｿｽ・ｽﾅゑｿｽ\n");
        break;
    }
}

// ・ｽ・ｽ・ｽﾌ擾ｿｽﾔゑｿｽ・ｽo・ｽ骼橸ｿｽﾌ擾ｿｽ・ｽ・ｽ
void IdleMapEnemyState::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
}

// ・ｽX・ｽe・ｽ[・ｽg・ｽﾏ更・ｽm・ｽF
STATE_TYPE_CHARACTER IdleMapEnemyState::StateCheck(CharacterBase* character)
{
    if (PlayerTargetCheck(character, 300.0f))
    {
        return STATE_TYPE_CHARACTER::TELOP_MAP_ENEMY_STATE;
    }

    return mStateNumber;
}

// ・ｽX・ｽV
void IdleMapEnemyState::Update(CharacterBase* character)
{
}

// ・ｽﾅ終・ｽX・ｽV
void IdleMapEnemyState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// ・ｽ`・ｽ・ｽ
void IdleMapEnemyState::Draw(CharacterBase* character)
{
    EnemyDataDraw(character);
}

// ・ｽ・ｽ・ｽS
void IdleMapEnemyState::Death(CharacterBase* character)
{
    MapEnemyDeath(character);
}

/*--------------------------------*/
/*・ｽy・ｽe・ｽ・ｽ・ｽb・ｽv・ｽ}・ｽb・ｽv・ｽG・ｽl・ｽ~・ｽ[・ｽe・ｽ[・ｽg・ｽz*/
/*--------------------------------*/
TelopMapEnemyState::TelopMapEnemyState(SCENE mapScene, std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
: IStateCharacter(stateChangeCriterias, STATE_TYPE_CHARACTER::TELOP_MAP_ENEMY_STATE, STATE_TYPE_CHARACTER::TELOP_MAP_ENEMY_STATE)
, MapEnemyProcess(mapScene)
{
}

// ・ｽ・ｽ・ｽﾌ擾ｿｽﾔに難ｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾌ擾ｿｽ・ｽ・ｽ
void TelopMapEnemyState::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
    switch (UtilChange::SceneState(mpSceneManager->GetNowScene()))
    {
    case SCENE::TOWN:
        //printfDx("・ｽe・ｽ・ｽ・ｽb・ｽv・ｽF・ｽ_・ｽ・ｽ・ｽW・ｽ・ｽ・ｽ・ｽ・ｽﾖ行・ｽ・ｽ・ｽﾉゑｿｽEnter・ｽL・ｽ[・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ\n");
        break;

    case SCENE::DUNGEON:
        //printfDx("・ｽe・ｽ・ｽ・ｽb・ｽv・ｽF・ｽo・ｽg・ｽ・ｽ・ｽﾖ行・ｽ・ｽ・ｽﾉゑｿｽEnter・ｽL・ｽ[・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽﾄゑｿｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ\n");
        break;
    }
}

// ・ｽ・ｽ・ｽﾌ擾ｿｽﾔゑｿｽ・ｽo・ｽ骼橸ｿｽﾌ擾ｿｽ・ｽ・ｽ
void TelopMapEnemyState::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
}

// ・ｽX・ｽe・ｽ[・ｽg・ｽﾏ更・ｽm・ｽF
STATE_TYPE_CHARACTER TelopMapEnemyState::StateCheck(CharacterBase* character)
{
    if (!PlayerTargetCheck(character,300.0f))
    {
        return STATE_TYPE_CHARACTER::IDLE_MAP_ENEMY_STATE;
    }

    return mStateNumber;
}

// ・ｽX・ｽV
void TelopMapEnemyState::Update(CharacterBase* character)
{
    if (mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::ENTER))
    {
        SetMapScene(character);
        clsDx();
    }
}

// ・ｽﾅ終・ｽX・ｽV
void TelopMapEnemyState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// ・ｽ`・ｽ・ｽ
void TelopMapEnemyState::Draw(CharacterBase* character)
{
    EnemyDataDraw(character);
}

// ・ｽ・ｽ・ｽS
void TelopMapEnemyState::Death(CharacterBase* character)
{
    MapEnemyDeath(character);
}
