#pragma once

#include "ObjectBases.h"
#include "StateBase.h"

/*----------------------*/
/*【リザルトUIステート】*/
/*----------------------*/

enum class RESULT_UI_STATE
{
	START_RESULT_UI_STATE = 0,			// 開始画面
};

/*----------------------*/
/*【開始画面UIステート】*/
/*----------------------*/
class StartResultUIState : public IStateUI
{
public:
	StartResultUIState();
	~StartResultUIState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui) override;

	/*更新*/
	int Update(UIBase* ui) override;

	/*決定*/
	int Decision(UIBase* ui) override;

	/*描画*/
	void Draw(UIBase* ui) override;
};