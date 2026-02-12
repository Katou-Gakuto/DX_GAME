#pragma once
class AttackManager;
class CameraManager;
class CollisionManager;
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

public:
	GameManager();
	~GameManager();

	// 初期化
	void Initilize();
	// 終了
	void Finailize();

	// 更新
	void Update();
	// 必要であれば削除する
	void DeleteAllIfNeeded();
	// 描画
	void Draw();

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
	/// <returns>攻撃マネジャー</returns>
	inline AttackManager* GetAttackManager() { return mpAttackManager; }

	/// <summary>
	/// カメラマネージャー取得
	/// </summary>
	/// <returns>カメラマネージャー</returns>
	inline CameraManager* GetCameraManager() { return mpCameraManager; }

	/// <summary>
	/// コリジョンマネージャー取得
	/// </summary>
	/// <returns>コリジョンマネージャー</returns>
	inline CollisionManager* GetCollisionManager() { return mpCollisionManager; }

	/// <summary>
	/// マップマネージャー取得
	/// </summary>
	/// <returns>マップマネージャー</returns>
	inline MapManager* GetMapManager() { return mpMapManager; }

	/// <summary>
	/// オブジェクトマネージャー取得
	/// </summary>
	/// <returns>オブジェクトマネージャー</returns>
	inline ObjectManager* GetObjectManager() { return mpObjectManager; }

	/// <summary>
	/// シーンマネージャー取得
	/// </summary>
	/// <returns>シーンマネージャー</returns>
	inline SceneManager* GetSceneManager() { return mpSceneManager; }

	/// <summary>
	/// ターゲットマネージャー取得
	/// </summary>
	/// <returns>ターゲットマネージャー</returns>
	inline TargetManager* GetTargetManager() { return mpTargetManager; }
};