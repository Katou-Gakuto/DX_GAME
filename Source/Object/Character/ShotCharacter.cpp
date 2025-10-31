#include "CollisionData.h"

#include "DxLib.h"

#include "ObjectBases.h"
#include "ShotCharacter.h"

ShotCharacter::ShotCharacter(bool nextSceneDeleteFlag, STATUS status)
: CharacterBase(nextSceneDeleteFlag, status)
, mnCameraID(-1)
{
}

ShotCharacter::~ShotCharacter()
{
}

// 攻撃リセット
void ShotCharacter::StopAttack()
{
}

#include "Master.h"
#include "CameraData.h"
#include "CameraManager.h"
#include "GameManager.h"

// キャラクター初期化
void ShotCharacter::CharacterInitilize()
{
    CameraData cameraData = CameraData();
    cameraData.cameraMode = CAMERA_MODE::PLAYER;
    cameraData.plusPosition = VGet(0.0f, 180.0f, 0.0f);
    cameraData.cameraDistance = 550.0f;
    cameraData.targetCharacter = this;
    cameraData.threeDFlag = true;
    cameraData.SetColor(F4Get(128, 128, 128, 0));
    mnCameraID = Master::mpGameManager->GetCameraManager()->NewCamera(cameraData);
    Master::mpGameManager->GetCameraManager()->SetCameraMode(mnCameraID);

    SetSpeed(1.0f);
}

// キャラクター終了
void ShotCharacter::CharacterFinalize()
{
    Master::mpGameManager->GetCameraManager()->DeleteCameraData(mnCameraID);
}
#include "Master.h"
#include "KeyState.h"
// キャラクター更新
void ShotCharacter::CharacterUpdate()
{
	if (Master::mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_UP))
	{
		SetFrontMove();
	}
	if (Master::mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_DOWN))
	{
		SetBackMove();
	}
	if (Master::mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_LEFT))
	{
		SetLeftMove();
	}
	if (Master::mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_RIGHT))
	{
		SetRightMove();
	}
}

// キャラクター最終更新
void ShotCharacter::CharacterLastUpdate()
{
}

// キャラクター描画
void ShotCharacter::CharacterDraw()
{

    VECTOR pos1;
    VECTOR pos2;

    SetUseZBufferFlag(true);

    pos1 = VGet(-10000.0f / 2.0f, 0.0f, -10000.0f / 2.0f);
    pos2 = VGet(-10000.0f / 2.0f, 0.0f, 10000.0f / 2.0f);
    for (int i = 0; i < 50; i++)
    {
        DrawLine3D(pos1, pos2, GetColor(0, 255, 0));
        pos1.x += 10000.0f / 50;
        pos2.x += 10000.0f / 50;
    }

    pos1 = VGet(-10000.0f / 2.0f, 0.0f, -10000.0f / 2.0f);
    pos2 = VGet(10000.0f / 2.0f, 0.0f, -10000.0f / 2.0f);
    for (int i = 0; i < 50; i++)
    {
        DrawLine3D(pos1, pos2, GetColor(255, 0, 0));
        pos1.z += 10000.0f / 50;
        pos2.z += 10000.0f / 50;
    }

	DrawSphere3D(VAdd(mvPosition, VGet(0.0f, 90.0, 0.0f)), 180.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}

// 当たり判定用
CollisionData ShotCharacter::CharacterCheck(const CollisionData& collisionData)
{
	return collisionData;
}