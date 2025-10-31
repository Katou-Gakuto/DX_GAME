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
		return SCENE::RESULT;
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
	}
}