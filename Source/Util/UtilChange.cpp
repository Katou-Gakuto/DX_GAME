#include <string>

#include "CharacterEnum.h"
#include "SceneEnum.h"

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

	return SCENE::NONE;
}

// シーンの名前を取得
std::string UtilChange::Name(SCENE scene)
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
	}
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