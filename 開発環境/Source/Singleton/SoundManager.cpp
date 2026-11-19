#include <iostream>>
#include <vector>

#include "DxLib.h"
#include "ResourceManager.h"
#include "SoundManager.h"

/*
* @fn コンストラクタ
*/
SoundManager::SoundManager()
: mnNowBackSoundHandle(-1)
, mnBackSoundVolume(100)
, mnSoundVolume(250)
{
	mnNowSoundHandles.clear();
	for (int i = 0; i < MAX_BACK_SOUND_NUMBER; i++) {
		mnBackSoundHandle[i] = -1;
	}
	for (int i = 0; i < MAX_SOUND_NUMBER; i++) {
		mnSoundHandle[i] = -1;
	}
	mnNow3DSoundHandles.clear();
}

/*
* @fn デストラクタ
*/
SoundManager::~SoundManager()
{
	InitSoundMem();
}

/*
* @fn Initilize
* @drief 初期化
*/
void SoundManager::Initilize()
{
	Set3DSoundOneMetre(100.0f);

	SetCreate3DSoundFlag(FALSE);
	// バックサウンド
	mnBackSoundHandle[static_cast<int>(BACK_SOUND::NORMAL_SOUND)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/NormalBackSound.mp3").c_str());
	mnBackSoundHandle[static_cast<int>(BACK_SOUND::MAP_SOUND)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/MapBackSound.wav").c_str());
	mnBackSoundHandle[static_cast<int>(BACK_SOUND::BATTLE_1_SOUND)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/Battle1BackSound.mp3").c_str());
	mnBackSoundHandle[static_cast<int>(BACK_SOUND::BATTLE_BOSS_1_SOUND)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/BattleBoss1BackSound.mp3").c_str());
	mnBackSoundHandle[static_cast<int>(BACK_SOUND::SELECT_DATA_SOUND)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/SelectDataBackSound.mp3").c_str());

	// サウンド
	mnSoundHandle[static_cast<int>(SOUND::SELECT_CHANGE)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/SelectChangeSound.mp3").c_str());
	mnSoundHandle[static_cast<int>(SOUND::DECISION)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/DecisionSound.mp3").c_str());
	mnSoundHandle[static_cast<int>(SOUND::OPEN)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/OpenSound.mp3").c_str());
	mnSoundHandle[static_cast<int>(SOUND::CLOSE)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/CloseSound.mp3").c_str());
	mnSoundHandle[static_cast<int>(SOUND::BEEP)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/BeepSound.mp3").c_str());
	mnSoundHandle[static_cast<int>(SOUND::POP_UP)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/PopUpSound.mp3").c_str());
	mnSoundHandle[static_cast<int>(SOUND::RECOVERY)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/RecoverySound.mp3").c_str());
	mnSoundHandle[static_cast<int>(SOUND::SCORE)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/ScoreSound.mp3").c_str());
	mnSoundHandle[static_cast<int>(SOUND::BATTLE_START)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/BattleStartSound.mp3").c_str());
	mnSoundHandle[static_cast<int>(SOUND::ROBOT_ATTACK_HIT)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/RobotAttackHitSound.mp3").c_str());
	mnSoundHandle[static_cast<int>(SOUND::ROBOT_ATTACK_STOP_AND_START)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/RobotAttackStopAndStartSound.mp3").c_str());
	mnSoundHandle[static_cast<int>(SOUND::ROBOT_FIXED_HIT_1)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/RobotFixedHitSound1.mp3").c_str());
	mnSoundHandle[static_cast<int>(SOUND::ROBOT_FIXED_HIT_2)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/RobotFixedHitSound2.mp3").c_str());
	mnSoundHandle[static_cast<int>(SOUND::ROBOT_Walk)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/RobotWalkSound.mp3").c_str());

	// 3Dサウンド
	SetCreate3DSoundFlag(TRUE);
	mn3DSoundHandle[static_cast<int>(SOUND_3D::ROBOT_ATTACK_HIT)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/RobotAttackHitSound.mp3").c_str());
	mn3DSoundHandle[static_cast<int>(SOUND_3D::ROBOT_ATTACK_STOP_AND_START)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/RobotAttackStopAndStartSound.mp3").c_str());
	mn3DSoundHandle[static_cast<int>(SOUND_3D::ROBOT_FIXED_HIT_1)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/RobotFixedHitSound1.mp3").c_str());
	mn3DSoundHandle[static_cast<int>(SOUND_3D::ROBOT_FIXED_HIT_2)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/RobotFixedHitSound2.mp3").c_str());
	mn3DSoundHandle[static_cast<int>(SOUND_3D::ROBOT_Walk)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/RobotWalkSound.mp3").c_str());
	mn3DSoundHandle[static_cast<int>(SOUND_3D::BEAM_CANNON_CHARGE)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/BeamCannonCharge.mp3").c_str());
	mn3DSoundHandle[static_cast<int>(SOUND_3D::BEAM_CANNON_SHOT)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/BeamCannonShot.mp3").c_str());
	mn3DSoundHandle[static_cast<int>(SOUND_3D::ROBOT_EYES_GLOW)] = LoadSoundMem((ResourceManager::msResourceFile + "Sound/RobotEyesGlow.mp3").c_str());
	SetCreate3DSoundFlag(FALSE);

	// 音量設定
	SetBackSoundVolumeProcess();
	//SetSoundVolumeProcess();
}

/*
* @fn Finalize
* @drief 終了処理
*/
void SoundManager::Finalize()
{
	for (int i = 0; i < mnNowSoundHandles.size(); i++) {
		DeleteSoundMem(mnNowSoundHandles[i]);
	}
	mnNowSoundHandles.clear();

	for (int i = 0; i < MAX_BACK_SOUND_NUMBER; i++) {
		DeleteSoundMem(mnBackSoundHandle[i]);
	}
	for (int i = 0; i < MAX_SOUND_NUMBER; i++) {
		DeleteSoundMem(mnSoundHandle[i]);
	}
}

/*
* @fn Update
* @drief 更新
*/
void SoundManager::Update()
{
	std::vector<int> deleteNumber;
	for (int i = 0; i < mnNowSoundHandles.size(); i++) {
		if (CheckSoundMem(mnNowSoundHandles[i]) == 0) {
			StopSoundMem(mnNowSoundHandles[i]);
			DeleteSoundMem(mnNowSoundHandles[i]);
			deleteNumber.push_back(i);
		}
	}
	for (int i = (deleteNumber.size() - 1); i >= 0; i--) {
		mnNowSoundHandles.erase(mnNowSoundHandles.begin() + deleteNumber[i]);
	}

	deleteNumber.clear();
	for (int i = 0; i < mnNow3DSoundHandles.size(); i++) {
		if (CheckSoundMem(mnNow3DSoundHandles[i]) == 0) {
			StopSoundMem(mnNow3DSoundHandles[i]);
			DeleteSoundMem(mnNow3DSoundHandles[i]);
			deleteNumber.push_back(i);
		}
	}
	for (int i = (deleteNumber.size() - 1); i >= 0; i--) {
		mnNow3DSoundHandles.erase(mnNow3DSoundHandles.begin() + deleteNumber[i]);
	}
}

/*
* @fn SetBackSound
* @drief 再生バックサウンド変更
*/
void SoundManager::SetBackSound(BACK_SOUND backuSound)
{
	int number = static_cast<int>(backuSound);

	StopSoundMem(mnNowBackSoundHandle);

	mnNowBackSoundHandle = mnBackSoundHandle[number];

	PlaySoundMem(mnNowBackSoundHandle, DX_PLAYTYPE_LOOP, TRUE);
}

/*
* @fn SetSound
* @drief 再生サウンド追加
*/
void SoundManager::SetSound(SOUND sound)
{
	int number = static_cast<int>(sound);

	mnNowSoundHandles.push_back(DuplicateSoundMem(mnSoundHandle[number]));

	ChangeVolumeSoundMem(mnSoundVolume, mnNowSoundHandles[mnNowSoundHandles.size() - 1]);

	PlaySoundMem(mnNowSoundHandles[mnNowSoundHandles.size() - 1], DX_PLAYTYPE_BACK, TRUE);
}

/*
* @fn Set3DSound
* @drief 再生3Dサウンド追加
*/
void SoundManager::Set3DSound(SOUND_3D sound3D, VECTOR position)
{
	int number = static_cast<int>(sound3D);

	SetCreate3DSoundFlag(TRUE);	

	mnNow3DSoundHandles.push_back(DuplicateSoundMem(mn3DSoundHandle[number]));

	Set3DPositionSoundMem(position, mnNow3DSoundHandles[mnNow3DSoundHandles.size() - 1]);
	Set3DRadiusSoundMem(2000.0f, mnNow3DSoundHandles[mnNow3DSoundHandles.size() - 1]);

	ChangeVolumeSoundMem(mnSoundVolume, mnNow3DSoundHandles[mnNow3DSoundHandles.size() - 1]);

	PlaySoundMem(mnNow3DSoundHandles[mnNow3DSoundHandles.size() - 1], DX_PLAYTYPE_BACK, TRUE);

	SetCreate3DSoundFlag(FALSE);
}

/*
* @fn SetBackSoundVolumeProcess
* @drief バックサウンドボリューム設定処理
*/
void SoundManager::SetBackSoundVolumeProcess()
{
	// バックサウンドの音量設定
	ChangeVolumeSoundMem(mnBackSoundVolume, mnNowBackSoundHandle);
	for (int i = 0; i < MAX_BACK_SOUND_NUMBER; i++) {
		ChangeVolumeSoundMem(mnBackSoundVolume, mnBackSoundHandle[i]);
	}
}

///*
//* @fn SetSoundVolumeProcess
//* @drief サウンドボリューム設定処理
//*/
//void SoundManager::SetSoundVolumeProcess()
//{
//	// サウンドの音量設定
//	for (int i = 0; i < mnNowSoundHandles.size(); i++) {
//		ChangeVolumeSoundMem(mnSoundVolume, mnNowSoundHandles[i]);
//	}
//	for (int i = 0; i < MAX_SOUND_NUMBER; i++) {
//		ChangeVolumeSoundMem(mnSoundVolume, mnSoundHandle[i]);
//	}
//
//	// 3Dサウンドの音量設定(サウンドの音量と同じ)
//	for (int i = 0; i < mnNow3DSoundHandles.size(); i++) {
//		ChangeVolumeSoundMem(mnSoundVolume, mnNow3DSoundHandles[i]);
//	}
//	for (int i = 0; i < MAX_3D_SOUND_NUMBER; i++) {
//		ChangeVolumeSoundMem(mnSoundVolume, mn3DSoundHandle[i]);
//	}
//}

/*
* @fn DrawBackSoundVolumeRate
* @drief バックサウンドのボリューム割合描画用
*/
void SoundManager::DrawBackSoundVolumeRate(float x1, float y1, float x2, float y2, float r, unsigned int color)
{
	DrawCircle(x1, y1, r, color);
	DrawCircle(x2, y2, r, color);
	DrawBox(x1, y1 - (r * 0.85), x2, y2 + (r * 1.1), color, TRUE);

	DrawCircle((x1 * (mnBackSoundVolume / 255.0f)) + (x2 * (1 - (mnBackSoundVolume / 255.0f))), (y1 + y2) * 0.5, r * 1.5, GetColor(0, 0, 0));
	DrawCircle((x1 * (mnBackSoundVolume / 255.0f)) + (x2 * (1 - (mnBackSoundVolume / 255.0f))), (y1 + y2) * 0.5, r * 1.4, color);
}

/*
* @fn DrawSoundVolumeRate
* @drief サウンドのボリューム割合描画用
*/
void SoundManager::DrawSoundVolumeRate(float x1, float y1, float x2, float y2, float r, unsigned int color)
{
	DrawCircle(x1, y1, r, color);
	DrawCircle(x2, y2, r, color);
	DrawBox(x1, y1 - (r * 0.85), x2, y2 + (r * 1.1), color, TRUE);

	DrawCircle((x1 * (mnSoundVolume / 255.0f)) + (x2 * (1 - (mnSoundVolume / 255.0f))), (y1 + y2) * 0.5, r * 1.5, GetColor(0, 0, 0));
	DrawCircle((x1 * (mnSoundVolume / 255.0f)) + (x2 * (1 - (mnSoundVolume / 255.0f))), (y1 + y2) * 0.5, r * 1.4, color);
}