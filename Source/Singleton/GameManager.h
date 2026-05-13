#pragma once
class AttackManager;
class CameraManager;
class CollisionManager;
class DotWeenManager;
class MapManager;
class ObjectManager;
class SceneManager;
class TargetManager;

class GameManager
{
private:
	// アタックマネージャー
	AttackManager* mpAttackManager;

	//カメラマネージャー
	CameraManager* mpCameraManager;

	// コリジョンマネージャー
	CollisionManager* mpCollisionManager;

	// DotWeenマネージャー
	DotWeenManager* mpDotWeenManager;

	// マップマネージャー
	MapManager* mpMapManager;
	
	// オブジェクトマネージャー
	ObjectManager* mpObjectManager;

	// シーンマネージャー
	SceneManager* mpSceneManager;

	//ターゲットマネージャー
	TargetManager* mpTargetManager;

	// UIナンバー
	int mnUINumber;

	// 未初期化フラグ
	bool mbUninitializedFlag;

public:
	GameManager();
	~GameManager();

	// DxLib_Init前初期化
	void DxLib_PreInit();

	// 初期化
	void Initilize();
	// 終了
	void Finalize();

	// 更新
	void Update();
	// 必要であれば削除する
	void DeleteAllIfNeeded();
	// 描画
	void Draw();
	
	/*----------------------------------*/
	/*【ウィンドウプロシージャ使用関数】*/
	/*----------------------------------*/

	/// <summary>別アプリ移動</summary>
	void OnDeactivate();
	/// <summary>別アプリからこのアプリに移動</summary>
	void OnActivate();

	/*------*/
	/*【UI】*/
	/*------*/

	/*UIナンバー増加*/
	int IncreaseUINumber();	
	/*UIナンバー減少*/
	void DecreaseUINumber();

	/// <summary>
	/// UIナンバー取得
	/// </summary>
	/// <returns>現在処理するUIナンバー</returns>
	inline int GetNowUINumber() const { return mnUINumber; }

	/*--------------------*/
	/*【マネージャー取得】*/
	/*--------------------*/
	
	/// <summary>
	/// 攻撃マネジャー取得
	/// </summary>
	/// <returns>マネージャー</returns>
	inline AttackManager* GetAttackManager() { return mpAttackManager; }

	/// <summary>
	/// カメラマネージャー取得
	/// </summary>
	/// <returns>マネージャー</returns>
	inline CameraManager* GetCameraManager() { return mpCameraManager; }

	/// <summary>
	/// コリジョンマネージャー取得
	/// </summary>
	/// <returns>マネージャー</returns>
	inline CollisionManager* GetCollisionManager() { return mpCollisionManager; }

	/// <summary>
	/// DotWeenマネージャー取得
	/// </summary>
	/// <returns>マネージャー</returns>
	inline DotWeenManager* GetDotWeenManager() { return mpDotWeenManager; }

	/// <summary>
	/// マップマネージャー取得
	/// </summary>
	/// <returns>マネージャー</returns>
	inline MapManager* GetMapManager() { return mpMapManager; }

	/// <summary>
	/// オブジェクトマネージャー取得
	/// </summary>
	/// <returns>マネージャー</returns>
	inline ObjectManager* GetObjectManager() { return mpObjectManager; }

	/// <summary>
	/// シーンマネージャー取得
	/// </summary>
	/// <returns>マネージャー</returns>
	inline SceneManager* GetSceneManager() { return mpSceneManager; }

	/// <summary>
	/// ターゲットマネージャー取得
	/// </summary>
	/// <returns>マネージャー</returns>
	inline TargetManager* GetTargetManager() { return mpTargetManager; }

	/*------------------*/
	/*【フラグ取得】*/
	/*------------------*/
	/// <summary>
	/// 未初期化フラグ取得
	/// </summary>
	/// <returns>フラグ</returns>
	inline bool GetUninitializedFlag() { return mbUninitializedFlag; }
};