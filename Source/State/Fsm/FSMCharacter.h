#pragma once


/*----------*/
/*【キャラクター有限状態マシン】*/
/*----------*/
class FSMCharacter : public FSMBase<IStateCharacter, STATE_TYPE_CHARACTER, CharacterBase>
{
public:
	FSMCharacter();

	/// <summary>終了</summary>
	void Finalize(CharacterBase* character);

	/*実行中状態をセットする*/
	void SetCurrentState(int id, CharacterBase* character);

	/*更新*/
	void Update(CharacterBase* character);
	/*最終更新*/
	void LastUpdate(CharacterBase* character);

	/*描画*/
	void Draw(CharacterBase* character);

	/*死亡*/
	void Death(CharacterBase* character);
};