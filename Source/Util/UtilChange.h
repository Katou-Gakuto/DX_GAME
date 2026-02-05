#pragma once
#include <iostream>
#include <string>

enum class CHARACTER_TYPE;
enum class SCENE;

namespace UtilChange
{
	/*シーンステートに変換*/
	SCENE SceneState(SCENE scene);

	// TODO: 後で関数名変更
	/*シーンの名前を取得*/
	std::string Name(SCENE scene);

	/*キャラクターの名前に変換*/
	std::string CharacterTypeToString(CHARACTER_TYPE characterType);
};