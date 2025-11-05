#include <vector>

#include "CollisionData.h"

#include "Master.h"

#include "CollisionManager.h"
#include "GameManager.h"
#include "ObjectBases.h"
#include "ObjectManager.h"
#include "TimeManager.h"

/*当たり判定反映処理*/
void CollisionManager::CollisionProcess()
{
	if (!Master::mpTimeManager->GetStopFlag())
	{
		std::vector<ObjectBase*> characterObject = Master::mpGameManager->GetObjectManager()->FindsByType_vector(OBJECT_TYPE::CHARACTER_BASE);
		std::vector<ObjectBase*> buildingObject = Master::mpGameManager->GetObjectManager()->FindsByType_vector(OBJECT_TYPE::BUILDING_BASE);

		// 全キャラクター分調べる
		for (int i = 0; i < characterObject.size(); i++)
		{
			CharacterBase* character = static_cast<CharacterBase*>(characterObject[i]);
			CollisionData setData;
			setData.position = character->GetPos();
			setData.vec = character->GetVec();
			setData.speed = character->GetSpeed();
			setData.size = 180.0f;

			// キャラクターとの当たり判定
			for (int j = 0; j < characterObject.size(); j++)
			{
				if (i != j)
				{
					setData = characterObject[j]->HitCheck(setData);
				}
			}

			// 建物との当たり判定
			for (int j = 0; j < buildingObject.size(); j++)
			{
				setData = buildingObject[j]->HitCheck(setData);
			}

			// 移動方向設定
			character->SetVec(setData.vec);
		}
	}
}