#include <vector>

#include "CollisionData.h"

#include "Master.h"

#include "CollisionManager.h"
#include "GameManager.h"
#include "MapManager.h"
#include "ObjectBase.h"
#include "ObjectManager.h"
#include "StopManager.h"

/*当たり判定反映処理*/
void CollisionManager::CollisionProcess()
{
	if (Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::GAME_OBJECT))
	{
		return;
	}

	std::vector<CharacterBase*> characterObject = Master::mpGameManager->GetObjectManager()->FindsByType_Character();
	std::vector<BuildingBase*> buildingObject = Master::mpGameManager->GetObjectManager()->FindsByType_Building();
	std::vector<AttackBase*> attackObject = Master::mpGameManager->GetObjectManager()->FindsByType_Attack();

	// 全キャラクター分調べる
	for (int i = 0; i < characterObject.size(); i++)
	{
		// データ入力
		CharacterBase* checkCharacter = characterObject[i];
		CollisionData setData;
		setData.position = checkCharacter->GetPos();
		setData.vec = checkCharacter->GetVec();
		setData.speed = checkCharacter->GetStatus()->GetNowSpeed();
		setData.objID = checkCharacter->GetID();
		setData.size = 180.0f;
		setData.collisionFlag = false;

		// キャラクターとの当たり判定
		for (int j = 0; j < characterObject.size(); j++)
		{
			if (i != j)
			{
				characterObject[j]->HitCheck(setData);
			}
		}
		setData.collisionFlag = false;

		// 建物との当たり判定
		for (int j = 0; j < buildingObject.size(); j++)
		{
			buildingObject[j]->HitCheck(setData);
		}
		setData.collisionFlag = false;

		// 攻撃との当たり判定
		for (int j = 0; j < attackObject.size(); j++)
		{
			attackObject[j]->HitCheck(setData);

			if (setData.collisionFlag)
			{
				attackObject[j]->HitCheck(setData);
				checkCharacter->Damage(attackObject[j]->GetAttackPower());

				setData.collisionFlag = false;
			}
		}
		setData.collisionFlag = false;

		// 移動方向設定
		checkCharacter->SetVec(setData.vec);
	}

	Master::mpGameManager->GetMapManager()->MapCollision();
}