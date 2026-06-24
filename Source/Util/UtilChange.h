#pragma once
#include <iostream>
#include <string>

#include "DxLib.h"

struct Vector2;

enum class CHARACTER_TYPE;
enum class SCENE;
enum class STATE_TYPE_CHARACTER;

namespace UtilChange
{
	/*シーンステートに変換*/
	SCENE SceneState(SCENE scene);

	// TODO: 後で関数名変更
	/*シーンの名前を取得*/
	std::string SceneTypeToString(SCENE scene);

	/*キャラクターの名前に変換*/
	std::string CharacterTypeToString(CHARACTER_TYPE characterType);

	/// <summary>ベクトルをベクトル2に変換(xy)</summary>
	Vector2 ChangeVector_XY(VECTOR src);
	/// <summary>ベクトルをベクトル2に変換(xz)</summary>
	Vector2 ChangeVector_XZ(VECTOR src);
	/// <summary>ベクトルをベクトル2に変換(yz)</summary>
	Vector2 ChangeVector_YZ(VECTOR src);

	/// <summary>ステートフリー枠に変換</summary>
	STATE_TYPE_CHARACTER ChangeStateFreeBorder(int plusNumber);
}