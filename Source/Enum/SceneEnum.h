#pragma once

/*メモ　シーンを新しく増やす時にやること
UtilChange::SceneStateに追加する
ステート処理書く
*/

// シーン
enum class SCENE
{
	NONE = -1,	// 無し
	START = 0,	// スタート
	TITLE,		// タイトル

	TOWN,		// 町
	TOWN_1,
	TOWN_2,
	TOWN_3,

	DUNGEON,	// ダンジョン
	DUNGEON_1,
	DUNGEON_2,
	DUNGEON_3,

	BATTLE,		// バトル
	BATTLE_1,
	BATTLE_2,
	BATTLE_3,

	RESULT,		// リザルト
	DUNGEON_RESULT,
	BATTLR_RESULT,

	GAME_OVER,	// ゲームオーバー

	GAME_LOOP,	// ゲームループ
	BATTLE_LOOP,	// バトルループ
};