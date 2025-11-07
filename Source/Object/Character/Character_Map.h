#pragma once

#include "ObjectBases.h"

class Character_Map : public CharacterBase
{
public:
	Character_Map(STATUS status);
	~Character_Map();

	/*攻撃開始(反動時間を返す)*/
	int StartAttck() override;

	/*攻撃停止*/
	void StopAttack() override;

private:
	/*キャラクター初期化*/
	void CharacterInitilize() override;
	/*キャラクター終了*/
	void CharacterFinalize() override;

	/*キャラクター更新*/
	void CharacterUpdate() override;
	/*キャラクター最終更新*/
	void CharacterLastUpdate() override;

	/*キャラクター描画*/
	void CharacterDraw() override;

	/*当たり判定用*/
	void HitCheck(CollisionData& collisionData) override;
};