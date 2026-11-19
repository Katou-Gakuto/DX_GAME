#pragma once
#include <iostream>
#include <vector>

enum class BACK_SOUND {
	NORMAL_SOUND = 0,	// ノーマル
	MAP_SOUND = 1,	// マップ
	BATTLE_1_SOUND = 2,	// バトル1
	BATTLE_BOSS_1_SOUND	= 3, // バトルボス1
	SELECT_DATA_SOUND = 4,	// データ選択時サウンド
	MAX_ENUM_BACK_SOUND_NUMBER = 5,	// バックサウンド最大数
};

enum class SOUND {
	SELECT_CHANGE = 0,	// 選択変更
	DECISION = 1,	// 決定
	OPEN = 2,	// メニュー開く
	CLOSE = 3,	// メニュー閉じる
	BEEP = 4,	// ビープ
	POP_UP = 5,	// ポップアップ
	RECOVERY = 6,	// 回復
	SCORE = 7,	// スコア
	BATTLE_START = 8,	// バトル開始
	ROBOT_ATTACK_HIT = 9,	// 攻撃が当たった(ロボット)
	ROBOT_ATTACK_STOP_AND_START = 11,	// 攻撃開始と終了(ロボット)
	ROBOT_FIXED_HIT_1 = 12,	// 固定物に当たった1(ロボット)
	ROBOT_FIXED_HIT_2 = 13,	// 固定物に当たった2(ロボット)
	ROBOT_Walk = 14,	// 歩き(ロボット)
	MAX_ENUM_SOUND_NUMER = 15,	// 最大サウンド数
};

enum class SOUND_3D {
	ROBOT_ATTACK_HIT = 0,	// 攻撃が当たった(ロボット)
	ROBOT_ATTACK_STOP_AND_START = 2,	// 攻撃開始と終了(ロボット)
	ROBOT_FIXED_HIT_1 = 3,	// 固定物に当たった1(ロボット)
	ROBOT_FIXED_HIT_2 = 4,	// 固定物に当たった2(ロボット)
	ROBOT_Walk = 5,	// 歩き(ロボット)

	BEAM_CANNON_CHARGE = 6,	// ビーム砲チャージ
	BEAM_CANNON_SHOT = 7,	// ビーム砲
	ROBOT_EYES_GLOW = 8,	// ロボットの目が光る

	MAX_ENUMSOUND_3DNUMBER = 9,	// 3Dサウンド最大数
};

class SoundManager
{
private:
	const int MAX_BACK_SOUND_NUMBER = static_cast<int>(BACK_SOUND::MAX_ENUM_BACK_SOUND_NUMBER);	// 最大バックサウンド数
	const int MAX_SOUND_NUMBER = static_cast<int>(SOUND::MAX_ENUM_SOUND_NUMER);	// 最大サウンド数
	const int MAX_3D_SOUND_NUMBER = static_cast<int>(SOUND_3D::MAX_ENUMSOUND_3DNUMBER);	// 最大3Dサウンド数

	int mnNowBackSoundHandle;	// 再生中バックサウンドハンドル
	std::vector<int> mnNowSoundHandles;	// 再生中サウンドハンドル
	std::vector<int> mnNow3DSoundHandles;	// 再生中3Dサウンドハンドル

	int mnBackSoundHandle[static_cast<int>(BACK_SOUND::MAX_ENUM_BACK_SOUND_NUMBER)];	// 全バックサウンドハンドル
	int mnSoundHandle[static_cast<int>(SOUND::MAX_ENUM_SOUND_NUMER)];	// 全サウンドハンドル
	int mn3DSoundHandle[static_cast<int>(SOUND_3D::MAX_ENUMSOUND_3DNUMBER)];

	int mnBackSoundVolume;	// バックサウンドの音量
	int mnSoundVolume;	// サウンドの音量

public:
	SoundManager();	// コンストラクタ
	~SoundManager();	// デストラクタ

	void Initilize();	// 初期化
	void Finalize();	// 終了処理
	void Update();		// 更新

	void SetBackSound(BACK_SOUND backuSound);	// 再生バックサウンド変更
	void SetSound(SOUND sound);	// 再生サウンド追加
	void Set3DSound(SOUND_3D sound3D, VECTOR position);	// 再生3Dサウンド追加

	void DownBackSoundVolume(int number) { mnBackSoundVolume -= number; if (mnBackSoundVolume < 0) { mnBackSoundVolume = 0; } }	// バックサウンド音量ダウン
	void UpBackSoundVolume(int number) { mnBackSoundVolume += number; if (mnBackSoundVolume > 255) { mnBackSoundVolume = 255; } }	// バックサウンド音量アップ
	void DownSoundVolume(int number) { mnSoundVolume -= number; if (mnSoundVolume < 0) { mnSoundVolume = 0; } }	// サウンド音量ダウン
	void UpSoundVolume(int number) { mnSoundVolume += number; if (mnSoundVolume > 255) { mnSoundVolume = 255; } }	// サウンド音量アップ

	int GetBackSoundVolume() { return mnBackSoundVolume; }	// バックサウンド音量取得
	int GetSoundVolume() { return mnSoundVolume; }	// サウンド音量取得

	void SetBackSoundVolumeProcess();	// バックサウンドボリューム設定処理
//	void SetSoundVolumeProcess();	// サウンドボリューム設定処理
	void DrawBackSoundVolumeRate(float x1, float y1, float x2, float y2, float r, unsigned int color);	// バックサウンドのボリューム割合描画用
	void DrawSoundVolumeRate(float x1, float y1, float x2, float y2, float r, unsigned int color);	// サウンドのボリューム割合描画用

	/// <summary>
	/// 3Dのリスナー位置を設定
	/// </summary>
	/// <param name="position">現在地</param>
	/// <param name="frontPosition">向いてる方向</param>
	void Set3DListenerPosition(VECTOR position, VECTOR frontPosition) { Set3DSoundListenerPosAndFrontPos_UpVecY(position, frontPosition); }
};