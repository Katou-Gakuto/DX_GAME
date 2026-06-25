#include <string>

#include "ObjectBases.h"
#include "ObjectManager.h"

// コンストラクタ
ObjectManager::ObjectManager()
: mpObjectBase(nullptr)
, mpCharacterBase(nullptr)
, mpBuildingBase(nullptr)
, mpAttackBase(nullptr)
, mpUIBase(nullptr)
, munSetID(0)
, munObjectCount(0)
{
}

// デストラクタ
ObjectManager::~ObjectManager()
{
}

/*------------------*/
/*     【処理】     */
/*------------------*/
// 初期化
void ObjectManager::Initilize()
{
	munSetID = 0;
	munObjectCount = 0;
}

// 終了
void ObjectManager::Finalize()
{
	// 全オブジェクト削除
	DeleteAll();
}

//　オブジェクトシーン最終初期化
void ObjectManager::ObjectSceneLastInitilize()
{
	if (mpObjectBase == nullptr)
	{
		return;
	}

	ObjectBase* workObject = mpObjectBase;
	do
	{
		workObject->SceneLastInitilize();

		workObject = workObject->GetNextObject();
	} while (workObject != nullptr);
}

// オブジェクト更新
void ObjectManager::ObjectUpdate()
{
	if (mpObjectBase == nullptr)
	{
		return;
	}

	ObjectBase* workObject = mpObjectBase;
	do
	{
		if (workObject->IsActiveFlag())
		{
			workObject->Update();
		}
		workObject = workObject->GetNextObject();
	} while (workObject != nullptr);
}

// オブジェクト最終更新
void ObjectManager::ObjectLastUpdate()
{
	if (mpObjectBase == nullptr)
	{
		return;
	}

	ObjectBase* workObject = mpObjectBase;
	do
	{
		if (workObject->IsActiveFlag())
		{
			workObject->LastUpdate();
		}
		workObject = workObject->GetNextObject();
	} while (workObject != nullptr);
}

// オブジェクト描画
void ObjectManager::ObjectDraw()
{
	if (mpObjectBase == nullptr)
	{
		return;
	}

	ObjectBase* workObject = mpObjectBase;
	do
	{
		if (workObject->IsActiveFlag())
		{
			workObject->Draw();
		}
		workObject = workObject->GetNextObject();
	} while (workObject != nullptr);
}

// リストにオブジェクトを追加する
int ObjectManager::Add(ObjectBase* object, OBJECT_TYPE typeNumber)
{
	munSetID += 1;
	munObjectCount += 1;

	bool setFlag = true;

	if (mpObjectBase == nullptr)
	{
		mpObjectBase = object;
		setFlag = false;
	}

	if (setFlag)
	{
		// 一番後ろの場所を探す。
		ObjectBase* currentObject = mpObjectBase;
		ObjectBase* nextObject = mpObjectBase->GetNextObject();

		while (nextObject != nullptr)
		{
			currentObject = nextObject;
			nextObject = currentObject->GetNextObject();
		}

		currentObject->SetNextObject(object);
		object->SetPrevObject(currentObject);
	}

	ObjectBase* checkObject = nullptr;
	switch ((OBJECT_TYPE)typeNumber)
	{
	case OBJECT_TYPE::BASE:
		return munSetID - 1;

	case OBJECT_TYPE::CHARACTER_BASE:
		if (mpCharacterBase == nullptr)
		{
			mpCharacterBase = object;
			return munSetID - 1;
		}
		checkObject = mpCharacterBase;
		break;

	case OBJECT_TYPE::BUILDING_BASE:
		if (mpBuildingBase == nullptr)
		{
			mpBuildingBase = object;
			return munSetID - 1;
		}
		checkObject = mpBuildingBase;
		break;

	case OBJECT_TYPE::ATTACK_BASE:
		if (mpAttackBase == nullptr)
		{
			mpAttackBase = object;
			return munSetID - 1;
		}
		checkObject = mpAttackBase;
		break;

	case OBJECT_TYPE::UI_BASE:
		if (mpUIBase == nullptr)
		{
			mpUIBase = object;
			return munSetID - 1;
		}
		checkObject = mpUIBase;
		break;

	}

	{
		// 一番後ろの場所を探す。
		ObjectBase* currentObject = checkObject;
		ObjectBase* nextObject = checkObject->GetNextObject(false);

		while (nextObject != nullptr)
		{
			currentObject = nextObject;
			nextObject = currentObject->GetNextObject(false);
		}

		currentObject->SetNextObject(object, false);
		object->SetPrevObject(currentObject, false);
	}

	return munSetID - 1;
}

// リストからオブジェクトを除外する
void ObjectManager::Delete(unsigned int id, OBJECT_TYPE typeNumber)
{
	munObjectCount -= 1;

	if (mpObjectBase == nullptr)
	{
		return;
	}

	ObjectBase* checkObject = GetTypeObject(typeNumber);
	if (typeNumber == OBJECT_TYPE::BASE)
	{
		checkObject = nullptr;
	}

	// 継承クラス
	do
	{
		if (checkObject != nullptr)
		{
			// もし最初のオブジェクトだった場合は特別な処理をする。
			if (checkObject->GetID() == id)
			{
				ObjectBase* next = checkObject->GetNextObject(false);
				ObjectBase* deleteObject = checkObject;
				switch ((OBJECT_TYPE)typeNumber)
				{
				case OBJECT_TYPE::CHARACTER_BASE:
					if (next != nullptr) {
						next->SetPrevObject(nullptr, false);
						mpCharacterBase = next;
					}
					else {
						mpCharacterBase = nullptr;
					}
					break;

				case OBJECT_TYPE::BUILDING_BASE:
					if (next != nullptr) {
						next->SetPrevObject(nullptr, false);
						mpBuildingBase = next;
					}
					else {
						mpBuildingBase = nullptr;
					}
					break;

				case OBJECT_TYPE::ATTACK_BASE:
					if (next != nullptr) {
						next->SetPrevObject(nullptr, false);
						mpAttackBase = next;
					}
					else {
						mpAttackBase = nullptr;
					}
					break;

				case OBJECT_TYPE::UI_BASE:
					if (next != nullptr) {
						next->SetPrevObject(nullptr, false);
						mpUIBase = next;
					}
					else {
						mpUIBase = nullptr;
					}
					break;

				}
				break;
			}

			// 以下、最初のオブジェクトではなかった場合の処理

			// 削除対象のオブジェクトを探索する
			ObjectBase* target = checkObject->GetNextObject(false);
			while (target->GetID() != id)
			{
				target = target->GetNextObject(false);

				if (target == nullptr)
				{
					break;
				}
			}

			// 削除対象のオブジェクトの前と後ろを繋げるために、一旦確保しておく
			ObjectBase* prev = target->GetPrevObject(false);
			ObjectBase* next = target->GetNextObject(false);

			// 削除対象のオブジェクトの前後を繋げ、削除対象を孤立させる
			prev->SetNextObject(next, false);
			if (next != nullptr)
			{
				next->SetPrevObject(prev, false);
			}
		}
	} while (false);

	// オブジェクトベース
	{
		// もし最初のオブジェクトだった場合は特別な処理をする。
		if (mpObjectBase->GetID() == id)
		{
			ObjectBase* next = mpObjectBase->GetNextObject();
			ObjectBase* deleteObject = mpObjectBase;
			if (next != nullptr)
			{
				next->SetPrevObject(nullptr);
				mpObjectBase = next;
			}
			else {
				mpObjectBase = nullptr;
			}

			deleteObject->Finalize();
			delete deleteObject;
			return;
		}

		// 以下、最初のオブジェクトではなかった場合の処理

		// 削除対象のオブジェクトを探索する
		ObjectBase* target = mpObjectBase->GetNextObject();
		while (target->GetID() != id)
		{
			if (target == nullptr)
			{
				return;
			}

			target = target->GetNextObject();
		}

		// 削除対象のオブジェクトの前と後ろを繋げるために、一旦確保しておく
		ObjectBase* prev = target->GetPrevObject();
		ObjectBase* next = target->GetNextObject();

		// 削除対象のオブジェクトの前後を繋げ、削除対象を孤立させる
		prev->SetNextObject(next);
		if (next != nullptr)
		{
			next->SetPrevObject(prev);
		}

		// 削除する
		target->Finalize();
		delete target;
		target = nullptr;
	}
}

// オブジェクト全削除
void ObjectManager::DeleteAll()
{
	// 最初のオブジェクトがないなら何もしない
	if (mpObjectBase == nullptr)
	{
		return;
	}

	// オブジェクトの全削除
	ObjectBase* target = mpObjectBase;
	do
	{
		ObjectBase* next = target->GetNextObject();
		Delete(target->GetID(), target->GetObjectTypeNumber());
		target = next;
	} while (target != nullptr);
}

// 必要であればオブジェクト削除を行う
void ObjectManager::DeleteAllIfNeeded()
{    // 最初のオブジェクトがないなら何もしない
	if (mpObjectBase == nullptr)
	{
		return;
	}

	// 削除フラグが立っているオブジェクトを順番に削除
	ObjectBase* target = mpObjectBase;
	do
	{
		ObjectBase* next = target->GetNextObject();
		if (target->IsDeleteFlag())
		{
			Delete(target->GetID(), target->GetObjectTypeNumber());
		}
		target = next;
	} while (target != nullptr);

}

/*------------------*/
/*     【取得】     */
/*------------------*/
/*------*/
/*【ID】*/
/*------*/
// IDからオブジェクトを取得
ObjectBase* ObjectManager::FindByID(int id, bool deleteGetFlag)
{
	if (mpObjectBase == nullptr)
	{
		return mpObjectBase;
	}

	ObjectBase* workObject = mpObjectBase;
	do
	{
		if (!workObject->IsDeleteFlag() || deleteGetFlag)
		{
			if (workObject->GetID() == id)
			{
				return workObject;
			}
		}
		workObject = workObject->GetNextObject();
	} while (workObject != nullptr);

	return workObject;
}


/*--------*/
/*【タグ】*/
/*--------*/
// タグからオブジェクトを取得
ObjectBase* ObjectManager::FindByTag(std::string tag, OBJECT_TYPE typeNumber, bool inactiveFlag, bool deleteGetFlag)
{
	// 種類別に調べる
	ObjectBase* checkObject = GetTypeObject(typeNumber);
	bool allBaseFlag = false;
	if ((OBJECT_TYPE)typeNumber == OBJECT_TYPE::BASE)
	{
		allBaseFlag = true;
	}

	if (checkObject == nullptr)
	{
		return checkObject;
	}

	ObjectBase* workObject = checkObject;
	do
	{
		if ((!workObject->IsDeleteFlag() || deleteGetFlag) && (workObject->IsActiveFlag() || inactiveFlag))
		{
			if (workObject->GetTag() == tag)
			{
				return workObject;
			}
		}
		workObject = workObject->GetNextObject(allBaseFlag);
	} while (workObject != nullptr);

	return workObject;
}

// タグから複数オブジェクトを取得(vector)
std::vector<ObjectBase*> ObjectManager::FindsByTag_vector(std::string tag, OBJECT_TYPE typeNumber, bool inactiveFlag, bool deleteGetFlag)
{
	ObjectBase* checkObject = GetTypeObject(typeNumber);
	bool allBaseFlag = false;
	if (typeNumber == OBJECT_TYPE::BASE)
	{
		allBaseFlag = true;
	}

	std::vector<ObjectBase*> result;
	result.clear();
	result.reserve(munObjectCount);

	if (checkObject == nullptr)
	{
		return result;
	}

	ObjectBase* workObject = checkObject;
	do
	{
		if ((!workObject->IsDeleteFlag() || deleteGetFlag) &&(workObject->IsActiveFlag() || inactiveFlag))
		{
			if (workObject->GetTag() == tag)
			{
				result.push_back(workObject);
			}
		}
		workObject = workObject->GetNextObject(allBaseFlag);
	} while (workObject != nullptr);

	return result;
}

// タグから複数オブジェクトを取得(list)
std::list<ObjectBase*> ObjectManager::FindsByTag_list(std::string tag, OBJECT_TYPE typeNumber, bool inactiveFlag, bool deleteGetFlag)
{
	ObjectBase* checkObject = GetTypeObject(typeNumber);
	bool allBaseFlag = false;
	if (typeNumber == OBJECT_TYPE::BASE)
	{
		allBaseFlag = true;
	}

	std::list<ObjectBase*> result;
	result.clear();

	if (checkObject == nullptr)
	{
		return result;
	}

	ObjectBase* workObject = checkObject;
	do
	{
		if ((!workObject->IsDeleteFlag() || deleteGetFlag) && (workObject->IsActiveFlag() || inactiveFlag))
		{
			if (workObject->GetTag() == tag)
			{
				result.push_back(workObject);
			}
		}
		workObject = workObject->GetNextObject(allBaseFlag);
	} while (workObject != nullptr);

	return result;
}

/*----------*/
/*【タイプ】*/
/*----------*/
// 指定タイプリストの先頭オブジェクトを取得
ObjectBase* ObjectManager::GetTypeObject(OBJECT_TYPE typeNumber)
{
	switch (typeNumber)
	{
	case OBJECT_TYPE::BASE:
		return mpObjectBase;

	case OBJECT_TYPE::CHARACTER_BASE:
		return mpCharacterBase;

	case OBJECT_TYPE::BUILDING_BASE:
		return mpBuildingBase;

	case OBJECT_TYPE::ATTACK_BASE:
		return mpAttackBase;

	case OBJECT_TYPE::UI_BASE:
		return mpUIBase;
	}

	return nullptr;
}

// 指定タイプを全取得(vector)
std::vector<ObjectBase*> ObjectManager::FindsByType_vector(OBJECT_TYPE typeNumber, bool inactiveFlag, bool deleteGetFlag)
{
	ObjectBase* checkObject = GetTypeObject(typeNumber);
	bool allBaseFlag = false;
	if (typeNumber == OBJECT_TYPE::BASE)
	{
		allBaseFlag = true;
	}

	std::vector<ObjectBase*> result;
	result.clear();
	result.reserve(munObjectCount);

	if (checkObject == nullptr)
	{
		return result;
	}

	ObjectBase* workObject = checkObject;
	do
	{
		if ((!workObject->IsDeleteFlag() || deleteGetFlag) && (workObject->IsActiveFlag() || inactiveFlag))
		{
			result.push_back(workObject);
		}
		workObject = workObject->GetNextObject(allBaseFlag);
	} while (workObject != nullptr);

	return result;
}

// 指定タイプを全取得(list)
std::list<ObjectBase*> ObjectManager::FindsByType_list(OBJECT_TYPE typeNumber, bool inactiveFlag, bool deleteGetFlag)
{
	ObjectBase* checkObject = GetTypeObject(typeNumber);
	bool allBaseFlag = false;
	if (typeNumber == OBJECT_TYPE::BASE)
	{
		allBaseFlag = true;
	}

	std::list<ObjectBase*> result;
	result.clear();

	if (checkObject == nullptr)
	{
		return result;
	}

	ObjectBase* workObject = checkObject;
	do
	{
		if ((!workObject->IsDeleteFlag() || deleteGetFlag) && (workObject->IsActiveFlag() || inactiveFlag))
		{
			result.push_back(workObject);
		}
		workObject = workObject->GetNextObject(allBaseFlag);
	} while (workObject != nullptr);

	return result;
}

// 全キャラクターベース取得
std::vector<CharacterBase*> ObjectManager::FindsByType_Character(bool inactiveFlag, bool deleteGetFlag)
{
	std::vector<CharacterBase*> result;
	result.clear();

	if (mpCharacterBase == nullptr)
	{
		return result;
	}

	ObjectBase* workObject = mpCharacterBase;
	do
	{
		if ((!workObject->IsDeleteFlag() || deleteGetFlag) && (workObject->IsActiveFlag() || inactiveFlag))
		{
			result.push_back(static_cast<CharacterBase*>(workObject));
		}
		workObject = workObject->GetNextObject(false);
	} while (workObject != nullptr);

	return result;
}

// 全ビルディングベース取得
std::vector<BuildingBase*> ObjectManager::FindsByType_Building(bool inactiveFlag, bool deleteGetFlag)
{
	std::vector<BuildingBase*> result;
	result.clear();

	if (mpBuildingBase == nullptr)
	{
		return result;
	}

	ObjectBase* workObject = mpBuildingBase;
	do
	{
		if ((!workObject->IsDeleteFlag() || deleteGetFlag) && (workObject->IsActiveFlag() || inactiveFlag))
		{
			result.push_back(static_cast<BuildingBase*>(workObject));
		}
		workObject = workObject->GetNextObject(false);
	} while (workObject != nullptr);

	return result;
}

// 全アタックベース取得
std::vector<AttackBase*> ObjectManager::FindsByType_Attack(bool inactiveFlag, bool deleteGetFlag)
{
	std::vector<AttackBase*> result;
	result.clear();

	if (mpAttackBase == nullptr)
	{
		return result;
	}

	ObjectBase* workObject = mpAttackBase;
	do
	{
		if ((!workObject->IsDeleteFlag() || deleteGetFlag) && (workObject->IsActiveFlag() || inactiveFlag))
		{
			result.push_back(static_cast<AttackBase*>(workObject));
		}
		workObject = workObject->GetNextObject(false);
	} while (workObject != nullptr);

	return result;
}


/*----------*/
/*【チーム】*/
/*----------*/
// チームからオブジェクトを取得
ObjectBase* ObjectManager::FindByTeam(int team, OBJECT_TYPE typeNumber, bool inactiveFlag, bool deleteGetFlag)
{
	// 種類別に調べる
	ObjectBase* checkObject = GetTypeObject(typeNumber);
	bool allBaseFlag = false;
	if (typeNumber == OBJECT_TYPE::BASE)
	{
		allBaseFlag = true;
	}

	if (checkObject == nullptr)
	{
		return checkObject;
	}

	ObjectBase* workObject = checkObject;
	do
	{
		if ((!workObject->IsDeleteFlag() || deleteGetFlag) && (workObject->IsActiveFlag() || inactiveFlag))
		{
			if (workObject->GetTeam() == team)
			{
				return workObject;
			}
		}
		workObject = workObject->GetNextObject(allBaseFlag);
	} while (workObject != nullptr);

	return workObject;
}

// チームから複数オブジェクト取得(vector)
std::vector<ObjectBase*> ObjectManager::FindsByTeam_vector(int team, OBJECT_TYPE typeNumber, bool inactiveFlag, bool deleteGetFlag)
{
	ObjectBase* checkObject = GetTypeObject(typeNumber);
	bool allBaseFlag = false;
	if (typeNumber == OBJECT_TYPE::BASE)
	{
		allBaseFlag = true;
	}

	std::vector<ObjectBase*> result;
	result.clear();
	result.reserve(munObjectCount);

	if (checkObject == nullptr)
	{
		return result;
	}

	ObjectBase* workObject = checkObject;
	do
	{
		if ((!workObject->IsDeleteFlag() || deleteGetFlag) && (workObject->IsActiveFlag() || inactiveFlag))
		{
			if (workObject->GetTeam() == team)
			{
				result.push_back(workObject);
			}
		}
		workObject = workObject->GetNextObject(allBaseFlag);
	} while (workObject != nullptr);

	return result;
}

// チームから複数オブジェクト取得(list)
std::list<ObjectBase*> ObjectManager::FindsByTeam_list(int team, OBJECT_TYPE typeNumber, bool inactiveFlag, bool deleteGetFlag)
{
	ObjectBase* checkObject = GetTypeObject(typeNumber);
	bool allBaseFlag = false;
	if (typeNumber == OBJECT_TYPE::BASE)
	{
		allBaseFlag = true;
	}

	std::list<ObjectBase*> result;
	result.clear();

	if (checkObject == nullptr)
	{
		return result;
	}

	ObjectBase* workObject = checkObject;
	do
	{
		if ((!workObject->IsDeleteFlag() || deleteGetFlag) && (workObject->IsActiveFlag() || inactiveFlag))
		{
			if (workObject->GetTeam() == team)
			{
				result.push_back(workObject);
			}
		}
		workObject = workObject->GetNextObject(allBaseFlag);
	} while (workObject != nullptr);

	return result;
}


/*------------------*/
/*     【設定】     */
/*------------------*/

/*--------*/
/*【削除】*/
/*--------*/
// 指定タグのオブジェクト削除フラグを有効化
void ObjectManager::DeleteSetTag(std::string tag)
{
	if (mpObjectBase == nullptr)
	{
		return;
	}

	ObjectBase* workObject = mpObjectBase;
	do
	{
		if (!workObject->IsDeleteFlag())
		{
			if (workObject->GetTag() == tag)
			{
				workObject->SetDeleteFlag(true);
			}
		}
		workObject = workObject->GetNextObject();
	} while (workObject != nullptr);
}

// 指定チームのオブジェクト削除フラグを有効化
void ObjectManager::DeleteSetTeam(int team)
{
	if (mpObjectBase == nullptr)
	{
		return;
	}

	ObjectBase* workObject = mpObjectBase;
	do
	{
		if (!workObject->IsDeleteFlag())
		{
			if (workObject->GetTeam() == team)
			{
				workObject->SetDeleteFlag(true);
			}
		}
		workObject = workObject->GetNextObject();
	} while (workObject != nullptr);
}

// 指定シーンで生成されたオブジェクトの削除フラグ有効化
void ObjectManager::DeleteSetScene(SCENE targetScene)
{
	if (mpObjectBase == nullptr)
	{
		return;
	}

	ObjectBase* workObject = mpObjectBase;
	do
	{
		if (workObject->GetObjectScene() == targetScene)
		{
			workObject->SetDeleteFlag(true);
		}

		workObject = workObject->GetNextObject();

	} while (workObject != nullptr);
}

/*----------*/
/*【非有効】*/
/*----------*/
// 指定タグのオブジェクトを非有効化
void ObjectManager::InactiveSetTag(std::string tag)
{
	if (mpObjectBase == nullptr)
	{
		return;
	}

	ObjectBase* workObject = mpObjectBase;
	do
	{
		if (!workObject->IsDeleteFlag())
		{
			if (workObject->GetTag() == tag)
			{
				workObject->SetActiveFlag(false);
			}
		}
		workObject = workObject->GetNextObject();
	} while (workObject != nullptr);
}

// 指定チームのオブジェクト削除フラグを非有効化
void ObjectManager::InactiveSetTeam(int team)
{
	if (mpObjectBase == nullptr)
	{
		return;
	}

	ObjectBase* workObject = mpObjectBase;
	do
	{
		if (!workObject->IsDeleteFlag())
		{
			if (workObject->GetTeam() == team)
			{
				workObject->SetActiveFlag(false);
			}
		}
		workObject = workObject->GetNextObject();
	} while (workObject != nullptr);
}

// 指定シーンで生成されたオブジェクトを非有効化する
void ObjectManager::InactiveSetScene(SCENE targetScene)
{
	if (mpObjectBase == nullptr)
	{
		return;
	}

	ObjectBase* workObject = mpObjectBase;
	do
	{
		if (workObject->GetObjectScene() == targetScene)
		{
			workObject->SetActiveFlag(false);
		}

		workObject = workObject->GetNextObject();

	} while (workObject != nullptr);
}

/*----------------*/
/*【オブジェクト】*/
/*----------------*/
// リストの先頭オブジェクトを設定
void ObjectManager::SetTypeObject(OBJECT_TYPE typeNumber, ObjectBase* setObject)
{
	switch (typeNumber)
	{
	case OBJECT_TYPE::BASE:
		mpObjectBase = setObject;
		break;

	case OBJECT_TYPE::CHARACTER_BASE:
		mpCharacterBase = setObject;
		break;

	case OBJECT_TYPE::BUILDING_BASE:
		mpBuildingBase = setObject;
		break;

	case OBJECT_TYPE::ATTACK_BASE:
		mpAttackBase = setObject;
		break;

	case OBJECT_TYPE::UI_BASE:
		mpUIBase = setObject;
		break;
	}
}