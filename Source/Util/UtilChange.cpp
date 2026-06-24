#include <string>

#include "CharacterEnum.h"
#include "SceneEnum.h"
#include "StateEnum.h"
#include "Vector2.h"

#include "DxLib.h"

#include "UtilChange.h"


// シーンステートに変換
SCENE UtilChange::SceneState(SCENE scene)
{
	switch ((SCENE)scene)
	{
	case SCENE::START:
		return SCENE::START;
		
	case SCENE::TITLE:
		return SCENE::TITLE;

	case SCENE::TOWN:
	case SCENE::TOWN_1:
	case SCENE::TOWN_2:
	case SCENE::TOWN_3:
		return SCENE::TOWN;

	case SCENE::DUNGEON:
	case SCENE::DUNGEON_1:
	case SCENE::DUNGEON_2:
	case SCENE::DUNGEON_3:
		return SCENE::DUNGEON;

	case SCENE::BATTLE:
	case SCENE::BATTLE_1:
	case SCENE::BATTLE_2:
	case SCENE::BATTLE_3:
		return SCENE::BATTLE;

	case SCENE::RESULT:
	case SCENE::BATTLR_RESULT:
	case SCENE::DUNGEON_RESULT:
		return SCENE::RESULT;

	case SCENE::GAME_OVER:
		return SCENE::GAME_OVER;
	}

	return scene;
}

// シーンの名前を取得
std::string UtilChange::SceneTypeToString(SCENE scene)
{
	switch (scene)
	{
	case SCENE::START:
		return "START";

	case SCENE::TITLE:
		return "TITLE";

	case SCENE::TOWN:
		return "TOWN";

	case SCENE::DUNGEON:
		return "DUNGEON";

	case SCENE::BATTLE:
		return "BATTLE";

	case SCENE::RESULT:
		return "RESUL";

	case SCENE::TOWN_1:
		return "町1";
	case SCENE::TOWN_2:
		return "町2";
	case SCENE::TOWN_3:
		return "町3";
	
	case SCENE::DUNGEON_1:
		return "ダンジョン1";
	case SCENE::DUNGEON_2:
		return "ダンジョン2";
	case SCENE::DUNGEON_3:
		return "ダンジョン3";

	case SCENE::BATTLE_1:
		return "バトル1";
	case SCENE::BATTLE_2:
		return "バトル2";
	case SCENE::BATTLE_3:
		return "バトル3";

	case SCENE::BATTLE_LOOP:
		return "BATTLE_LOOP";

	case SCENE::GAME_LOOP:
		return "GAME_LOOP";

	case SCENE::BATTLR_RESULT:
		return "BATTLE_RESULT";
	}

	return "OTHER";
}

// キャラクターの名前に変換
std::string UtilChange::CharacterTypeToString(CHARACTER_TYPE characterType)
{
	switch (characterType)
	{
	case CHARACTER_TYPE::ROBOT:
		return "ロボット";
	}
}

/// <summary>ベクトルをベクトル2に変換(xy)</summary>
Vector2 UtilChange::ChangeVector_XY(VECTOR src)
{
	return Vector2(src.x, src.y);
}


/// <summary>ベクトルをベクトル2に変換(xz)</summary>
Vector2 UtilChange::ChangeVector_XZ(VECTOR src)
{
	return Vector2(src.x, src.z);
}

/// <summary>ベクトルをベクトル2に変換(yz)</summary>
Vector2 UtilChange::ChangeVector_YZ(VECTOR src)
{
	return Vector2(src.y, src.z);
}

/// <summary>ステートフリー枠に変換</summary>
STATE_TYPE_CHARACTER UtilChange::ChangeStateFreeBorder(int plusNumber)
{
	return static_cast<STATE_TYPE_CHARACTER>(plusNumber + static_cast<int>(STATE_TYPE_CHARACTER::STATE_FREE_BORDER));
}