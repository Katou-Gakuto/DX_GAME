#pragma once

// ステート種類 キャラクター
enum class STATE_TYPE_CHARACTER
{

    // StateEnemy
	IDLE_ENEMY_STATE = 0,
	MOVE_ENEMY_STATE,
	ATTACK_IN_ENEMY_STATE,
	ATTACK_ENEMY_STATE,
	RIGHT_AVOID_ENEMY_STATE,
	LEFT_AVOID_ENEMY_STATE,
	ESCAPE_ENEMY_STATE,
    
    // StateMapEnemy
	IDLE_MAP_ENEMY_STATE,// = 0,
	TELOP_MAP_ENEMY_STATE,

    // StatePlayer
	IDLE_PLAYER_STATE,// = 0,
	MOVE_PLAYER_STATE,
	NORMAL_ATTACK_PLAYER_STATE,
	SPCEIAL_ATTACK_PLAYER_STATE,
	FLINCH_PLAYER_STATE,	// 怯み
	AVOID_PLAYER_STATE,	// 避ける
	GUARD_PLAYER_STATE,	// ガード
	FALL_DOWN_PLAYER_STATE,	// 倒れる
	JUMP_ATTACK_PLAYER_STATE,	// ジャンプ攻撃
};

// ステート種類 UI
enum class STATE_TYPE_UI
{
    // StateGameUI
    NORMAL_GAME_UI_STATE = 0,   // 通常
    PAUSE_GAME_UI_STATE,	// ポーズ
    DRAW_PLAYER_DATA_UI_STATE,  // プレイヤー情報描画
    CONFIG_CHANGE_UI_STATE, // 設定変更
    GAME_END_UI_STATE,  // ゲーム終了

    // StateConfigUI
    SELECT_CONFIG_STATE,// = 0,// 選択コンフィグデータ
    MINIMAP_CONFIG_STATE,   // ミニマップ設定
    SOUND_CONFIG_STATE,     // サウンド設定
    CAMERA_CONFIG_STATE,    // カメラ設定

    
    // StateTitleUI
	START_TITLE_UI_STATE,// = 0,			// 開始画面
	SELECT_TITLE_UI_STATE,				// 選択
    /*選択開始*/
	NEW_DATA_CHECK_TITLE_UI_STATE,		// 新しいデータの入る場所があるか確認する
	DATA_SELECT_TITLE_UI_STATE,			// データ選択
	TUTORIAL_TITLE_UI_STATE,			// チュートリアル開始
	SETTING_TITLE_UI_STATE,				// セッティング
	/*新データ関係*/
	CHARACTER_SELECT_TITLE_UI_STATE,	// キャラクター種類選択
	PLAYER_NAME_TITLE_UI_STATE,			// プレイヤー名設定
	INPUT_CHECK_TITLE_UI_STATE,			// 入力情報の最終確認
	/*セッティング関係*/
	SCREEN_SIZE_TITLE_UI_STATE,			// 画面サイズ
	VOLUME_TITLE_UI_STATE,				// 音量

    // StateResultUI
	START_RESULT_UI_STATE,// = 0,			// 開始画面
};