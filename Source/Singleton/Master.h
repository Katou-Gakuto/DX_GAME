#pragma once

class DataManager;
class EndManager;
class FadeManager;
class GameManager;
#if _DEBUG
class ImguiManager;
#endif
class KeyState;
class LoadingManager;
class ResourceManager;
class StopManager;
class TelopManager;
class TimeManager;

class Master
{
public:
	static DataManager* mpDataManager;	// データマネージャー
	static EndManager* mpEndManager;	// エンドマネージャー
	static FadeManager* mpFadeManager;	// フェードマネージャー
	static GameManager* mpGameManager;	// ゲームマネージャー
#if _DEBUG
	static ImguiManager* mpImguiManager;	// Imguiマネージャー
#endif
	static KeyState* mpKeyState;	// キーステート
	static LoadingManager* mpLoadingManager;	// ローディングマネージャー
	static ResourceManager* mpResourceManager;	// リソースマネージャー
	static StopManager* mpStopManager;	// ストップマネージャー
	static TelopManager* mpTelopManager;	// テロップマネージャー
	static TimeManager* mpTimeManager;	// タイムマネージャー

	/*マスター所持物全削除処理*/
	static void AllDelete();
};