#pragma once

// ステート種類 キャラクター
enum class STATE_TYPE_CHARACTER
{

};

// ステート種類 UI
enum class STATE_TYPE_UI
{
    NORMAL_GAME_UI_STATE = 0,   // 通常
    PAUSE_GAME_UI_STATE,	// ポーズ

    DRAW_PLAYER_DATA_UI_STATE,  // プレイヤー情報描画
    CONFIG_CHANGE_UI_STATE, // 設定変更

    GAME_END_UI_STATE,  // ゲーム終了
};