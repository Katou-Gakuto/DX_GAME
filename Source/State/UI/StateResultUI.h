#pragma once
#include <vector>

#include "GenericEnum.h"
#include "DrawData.h"
#include "Status.h"

#include "ObjectBase_UI.h"
#include "StateUIBase.h"

/*----------------------*/
/*【リザルトUIステート】*/
/*----------------------*/

// enum class RESULT_UI_STATE
// {
// 	START_RESULT_UI_STATE = 0,			// 開始画面
// };

/*----------------------*/
/*【開始画面UIステート】*/
/*----------------------*/
class StartResultUIState : public IStateUI
{
private:
	enum RESULT_DRAW_NUMBER_TYPE
	{
		PRE_LEVEL = 0,
		PRE_EXP,
		PRE_MAX_HP,
		PRE_HP,
		PRE_ATTACK,
		PRE_SPEED,

		LEVEL,
		EXP,
		MAX_HP,
		HP,
		ATTACK,
		SPEED,

		MAX
	};

	// 数字描画情報
	DRAW_DATA mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::MAX];

	// 描画する数字ポインター
	int mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::MAX];

	// 画像の描画個所
	Vector2_Int mstNumberDrawGraphPos[NUMBERS_ENUM::NUMBERS_ENUM_MAX];

	// 描画情報
	std::vector<DRAW_DATA> mstDrawDatas;

public:
	StartResultUIState();
	~StartResultUIState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui, STATE_TYPE_UI preState) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui, STATE_TYPE_UI newState) override;

	/*更新*/
	void Update(UIBase* ui) override;

	/*決定*/
	void Decision(UIBase* ui) override;

	/*描画*/
	void Draw(UIBase* ui) override;

private:
	/*数字描画*/
	void DrawNumber();

	/*数字情報を描画する*/
	void NumberDataDraw(DRAW_DATA numberDrawData, int number);
};