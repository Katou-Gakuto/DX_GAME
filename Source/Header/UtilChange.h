#pragma once
#include <iostream>
#include <string>

enum class SCENE;

namespace UtilChange
{
	/*シーンステートに変換*/
	SCENE SceneState(SCENE scene);

	/*シーンの名前を取得*/
	std::string Name(SCENE scene);
};