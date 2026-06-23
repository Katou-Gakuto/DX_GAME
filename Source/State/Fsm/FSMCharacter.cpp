#include <map>

#include "FSM.h"
#include "FSMCharacter.h"
#include "ObjectBase_Character.h"
#include "StateCharacterBase.h"

/*------------------------------*/
/*【キャラクター有限状態マシン】*/
/*------------------------------*/

FSMCharacter::FSMCharacter()
: FSMBase()
{
}

// 終了
void FSMCharacter::Finalize(CharacterBase* character)
{
	mmStateMap[mCurrentState]->Finalize(character);
}

// 更新
void FSMCharacter::Update(CharacterBase* character)
{
	CheckChangeState(character);

	mmStateMap[mCurrentState]->Update(character);
}

// 最終更新
void FSMCharacter::LastUpdate(CharacterBase* character)
{
	mmStateMap[mCurrentState]->LastUpdate(character);
}

// 描画
void FSMCharacter::Draw(CharacterBase* character)
{
	mmStateMap[mCurrentState]->Draw(character);
}

// 死亡
void FSMCharacter::Death(CharacterBase* character)
{
	mmStateMap[mCurrentState]->Death(character);
}