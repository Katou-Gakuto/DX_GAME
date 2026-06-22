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

// 実行中状態をセットする
void FSMCharacter::SetCurrentState(int id, CharacterBase* character)
{
	mCurrentState = id;
	mmStateMap[mCurrentState]->OnEnter(character);
}

// 更新
void FSMCharacter::Update(CharacterBase* character)
{
	int nextState = mmStateMap[mCurrentState]->StateCheck(character);
	if (mCurrentState != nextState)
	{
		mmStateMap[mCurrentState]->OnExit(character);//現在のStateの終了処理
		mmStateMap[nextState]->OnEnter(character);//新しいStateの開始処理
		mCurrentState = nextState;//新しいStateを設定
	}

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