#pragma once

class EndManager;
class GameManager;
class KeyState;
class LoadingManager;
class ResourceManager;
class TimeManager;

class Master
{
public:
	static EndManager* mpEndManager;	// エンドマネージャー
	static GameManager* mpGameManager;	// ゲームマネージャー
	static KeyState* mpKeyState;	// キーステート
	static LoadingManager* mpLoadingManager;	// ローディングマネージャー
	static ResourceManager* mpResourceManager;	// リソースマネージャー
	static TimeManager* mpTimeManager;	// タイムマネージャー

	/*マスター所持物全削除処理*/
	static void AllDelete();
};