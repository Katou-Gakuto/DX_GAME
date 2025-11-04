#pragma once
class AttackManager;
class CameraManager;
class ObjectManager;
class SceneManager;

class GameManager
{
private:
	// アタックマネージャー
	AttackManager* mpAttackManager;

	//ターゲット

	//カメラマネージャー
	CameraManager* mpCameraManager;

	//マップ
	// オブジェクトマネージャー
	ObjectManager* mpObjectManager;

	// シーンマネージャー
	SceneManager* mpSceneManager;

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
	/// オブジェクトマネージャー取得
	/// </summary>
	/// <returns>オブジェクトマネージャー</returns>
	inline ObjectManager* GetObjectManager() { return mpObjectManager; }

	/// <summary>
	/// シーンマネージャー取得
	/// </summary>
	/// <returns>シーンマネージャー</returns>
	inline SceneManager* GetSceneManager() { return mpSceneManager; }
};