#pragma once

#include "DxLib.h"

class ModelBase
{
private:
	// サイズ
	VECTOR mvSize;

public:
	ModelBase();
	~ModelBase();

	/*初期化*/
	void Initilize();
	/*終了*/
	void Finalize();

	/*--------*/
	/*【取得】*/
	/*--------*/

	/*サイズ取得*/
	inline VECTOR GetSize() const { return mvSize; }

	/*--------*/
	/*【設定】*/
	/*--------*/

	/*サイズ設定*/
	inline void SetSize(VECTOR size) { mvSize = size; }

	/*----------------*/
	/*【継承モデル用】*/
	/*----------------*/
public:
	/*モデル描画*/
	virtual void ModelDraw() = 0;

protected:
	/*継承モデル初期化*/
	virtual void ModelInitilize() = 0;
	/*継承モデル終了*/
	virtual void ModelFinalize() = 0;
};