#include <map>

#include "AttackEnum.h"
#include "DrawData.h"
#include "ResourceData.h"

#include "Master.h"

#include "AnimationBase.h"
#include "AttackManager.h"
#include "DataManager.h"
#include "DrawManager.h"
#include "FSM.h"
#include "GameManager.h"
#include "ModelsControllerBase.h"
#include "ObjectBase.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "StateBase.h"
#include "StopManager.h"
#include "UtilCalc.h"
#include "UtilFactorys.h"

/*------------------------------------------*/
/*          【オブジェクトベース】          */
/*------------------------------------------*/
// コンストラクタ
ObjectBase::ObjectBase(OBJECT_TYPE objectType, bool isActiveFlag, bool nextSceneDeleteFlag)
: mnTag("")
, mnTeam(0)
, mbIsDeleteFlag(false)
, mbIsActiveFlag(isActiveFlag)
, mbNextSceneDeleteFlag(nextSceneDeleteFlag)
, meObjectType(objectType)
{
	mpNextObject = nullptr;
	mpPrevObject = nullptr;
	mpInheritClassNextObject = nullptr;
	mpInheritClassPrevObject = nullptr;

	mullFlags.Init();

	munID = Master::mpGameManager->GetObjectManager()->Add(this, objectType);

	meObjectScene = (SCENE)Master::mpGameManager->GetSceneManager()->GetFSMScene()->GetCurrentState();
}

// デストラクタ
ObjectBase::~ObjectBase()
{
}




#ifdef _DEBUG
#include <cassert>
bool DEBUG_OBJECT_POINT_CHECK(void* p, bool check)
{
	if (p != nullptr)
	{
		// ポインタを整数に変換
		uintptr_t addr = reinterpret_cast<uintptr_t>(p);

		// 上位32ビットを取り出す
		uint32_t upper = static_cast<uint32_t>(addr >> 32);

		// 0かどうか確認
		if (check)
		{
			assert(upper != 0 && "上位32ビットは0です\n");
		}
		if (upper == 0)
		{
			return true;
		}
		return false;
	}

	return false;
}
#endif