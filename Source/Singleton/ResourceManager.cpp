#include <map>
#include <string>
#include <vector>

#include "ResourceEnum.h"
#include "ResourceData.h"
#include "Vector2.h"

#include "DxLib.h"
#include "EffekseerForDXLib.h"

#include "Master.h"

#include "EndManager.h"
#include "ResourceManager.h"

std::string ResourceManager::msResourceFile = "../Resource/";
DisplaySize ResourceManager::mstDisplaySize = DisplaySize();
/*--------*/
/*【共通】*/
/*--------*/
ResourceManager::ResourceManager()
: mbEffectDrawFlag(false)
, mnEffectDrawPreHandle(-1)
{
	// シャドウマップ
	mnShadowMapHandle = -1;

	// 3Dモデル
	mmModelHandle.clear();
	mmModelCount.clear();

	// 画像
	mmGraphHandle.clear();
	mmGraphCount.clear();
	mmDivGraphHandle.clear();
	msDivGraphFileNames.clear();

	// エフェクト
	mmEffectHandle.clear();
	mmEffectCount.clear();
}
ResourceManager::~ResourceManager()
{
}

// 初期化
void ResourceManager::Initilize()
{
	// ディスプレイサイズ設定
	Vector2_Int setDisplaySize;
    GetScreenState(&setDisplaySize.x, &setDisplaySize.y, &mstDisplaySize.colorBit);
	mstDisplaySize = setDisplaySize;

	ShadowMapInit();

	EffectInit();
}

// 終了
void ResourceManager::Finailize()
{
	{// シャドウマップ
		DeleteShadowMap(mnShadowMapHandle);
	}

	{// 3Dモデル
		MV1InitModel();
		mmModelCount.clear();
		mmModelHandle.clear();
	}

	{// 画像
		for (std::pair<std::string, int> graphHandle : mmGraphHandle)
		{
			DeleteGraph(graphHandle.second);
		}
		mmGraphHandle.clear();
		mmGraphCount.clear();

		for (const std::pair<std::string, DIV_GRAPH_DATA>& divHandle : mmDivGraphHandle)
		{
			for (int i = 0; i < divHandle.second.allNum; i++)
			{
				DeleteGraph(*(divHandle.second.handle + i));
			}
		}
		mmDivGraphHandle.clear();
		msDivGraphFileNames.clear();
	}

	{// 動画
		for (std::pair<std::string, int> moveiHandle : mmMovieHandle)
		{
			DeleteGraph(moveiHandle.second);
		}
		mmMovieHandle.clear();
		mmMovieCount.clear();
	}

	{// サウンド
	}

	{// エフェクト
		EffectFinailize();
	}
}

// 開始描画
void ResourceManager::StartDraw()
{
	// シャドウマップへの描画の準備
	ShadowMap_DrawSetup(mnShadowMapHandle);
}
// 中間描画
void ResourceManager::MiddleDraw()
{
	// シャドウマップへの描画を終了
	ShadowMap_DrawEnd();
	// 描画に使用するシャドウマップを設定
	SetUseShadowMap(0, mnShadowMapHandle);

}
// 終了描画
void ResourceManager::LastDraw()
{
	// エフェクト描画処理
	EffectDrawProcess();
}

// 描画データ解放
void ResourceManager::DrawDataRelease()
{
	// 描画に使用するシャドウマップの設定を解除
	SetUseShadowMap(0, -1);
	
	// エフェクト描画フラグ無効化
	mbEffectDrawFlag = false;
}

// モデル描画
void ResourceManager::DrawModelHandle(int modelHandle)
{
	MV1DrawModel(modelHandle);
}

// 頂点情報による描画
void ResourceManager::DrawIndexed(const VERTEX3D *VertexArray, int VertexNum, const unsigned short *IndexArray, int PolygonNum, int GrHandle, int TransFlag)
{
	DrawPolygonIndexed3D(VertexArray, VertexNum, IndexArray, PolygonNum, GrHandle, TransFlag);
}

// 画像や動画の描画
void ResourceManager::DrawData_Graph(DRAW_GRAPH_DATA drawData)
{
	int failureFlag;
	switch (drawData.drawType)
	{
	case DRAW_GRAPH_TYPE::NORMAL:
		failureFlag = DrawGraph(drawData.pos.x, drawData.pos.y, drawData.handle, drawData.transFlag);
		break;

	case DRAW_GRAPH_TYPE::TURN:
		failureFlag = DrawTurnGraph(drawData.pos.x, drawData.pos.y, drawData.handle, drawData.transFlag);
		break;

	case DRAW_GRAPH_TYPE::EXTEND:
		failureFlag = DrawExtendGraph(drawData.pos.x, drawData.pos.y, drawData.extPos.x, drawData.extPos.y, drawData.handle, drawData.transFlag);
		break;

	case DRAW_GRAPH_TYPE::SIZE:
		failureFlag = DrawExtendGraph(drawData.pos.x, drawData.pos.y, drawData.pos.x + drawData.size.x, drawData.pos.y + drawData.size.y, drawData.handle, drawData.transFlag);
		break;

	case DRAW_GRAPH_TYPE::ROTA:
		failureFlag = DrawRotaGraph(drawData.pos.x, drawData.pos.y, drawData.extRate.z, drawData.angle, drawData.handle, drawData.transFlag, drawData.turnFlag.x, drawData.turnFlag.y);
		break;

	case DRAW_GRAPH_TYPE::ROTA_CENTER:
		failureFlag = DrawRotaGraph2(drawData.pos.x, drawData.pos.y, drawData.centerPos.x, drawData.centerPos.y, drawData.extRate.z, drawData.angle, drawData.handle, drawData.transFlag, drawData.turnFlag.x, drawData.turnFlag.y);
		break;

	case DRAW_GRAPH_TYPE::ROTA_EXTEND_XY:
		failureFlag = DrawRotaGraph3(drawData.pos.x, drawData.pos.y, drawData.centerPos.x, drawData.centerPos.y, drawData.extRate.x, drawData.extRate.y, drawData.angle, drawData.handle, drawData.transFlag, drawData.turnFlag.x, drawData.turnFlag.y);
		break;

	case DRAW_GRAPH_TYPE::FREE:
		failureFlag = DrawModiGraph(drawData.upLeft.x, drawData.upLeft.y, drawData.upRight.x, drawData.upRight.y, drawData.downRight.x, drawData.downRight.y, drawData.downLeft.x, drawData.downLeft.y, drawData.handle, drawData.transFlag);
		break;

	case DRAW_GRAPH_TYPE::RECT:
		failureFlag = DrawRectGraph(drawData.pos.x, drawData.pos.y, drawData.graphPos.x, drawData.graphPos.y, drawData.size.x, drawData.size.y, drawData.handle, drawData.transFlag, drawData.turnFlag.x, drawData.turnFlag.y);
		break;
	}
}

// シャドウマップの初期化
void ResourceManager::ShadowMapInit()
{
	// シャドウマップハンドル作成
	mnShadowMapHandle = MakeShadowMap(1024, 1024);
	// シャドウマップが想定するライトの方向もセット
	SetShadowMapLightDirection(mnShadowMapHandle, VGet( 0.5f, -0.5f, 0.5f));

	// シャドウマップに描画する範囲を設定
	SetShadowMapDrawArea(mnShadowMapHandle, VGet(-10000.0f, -1.0f, -10000.0f), VGet(10000.0f, 10000.0f, 10000.0f));
}

// 描画情報取得
DRAW_GRAPH_DATA ResourceManager::GetDrawGraphData(int handle, int x, int y)
{
	DRAW_GRAPH_DATA drawData;
	drawData.drawType = DRAW_GRAPH_TYPE::NORMAL;
	if (handle != -1)
	{
		drawData.handle = handle;
	}
	drawData.transFlag = TRUE;

	drawData.pos.x = x;
	drawData.pos.y = y;

	return drawData;
}

// 描画情報取得
DRAW_GRAPH_DATA ResourceManager::GetDrawGraphData(int handle, int x, int y, int sizeX, int sizeY)
{
	DRAW_GRAPH_DATA drawData;
	drawData.drawType = DRAW_GRAPH_TYPE::SIZE;
	if (handle != -1)
	{
		drawData.handle = handle;
	}
	drawData.transFlag = TRUE;

	drawData.pos.x = x;
	drawData.pos.y = y;

	drawData.size.x = sizeX;
	drawData.size.y = sizeY;

	return drawData;
}

// 描画情報取得
DRAW_GRAPH_DATA ResourceManager::GetDrawGraphData(int handle, int x, int y, float sizeXRatio, float sizeYRatio)
{
	DRAW_GRAPH_DATA drawData;
	drawData.drawType = DRAW_GRAPH_TYPE::SIZE;
	if (handle != -1)
	{
		drawData.handle = handle;
	}
	drawData.transFlag = TRUE;

	drawData.pos.x = x;
	drawData.pos.y = y;

	drawData.size = mstDisplaySize.LeftUp_Ratio(Vector2(sizeXRatio, sizeYRatio));

	return drawData;
}

// 描画情報取得
DRAW_GRAPH_DATA ResourceManager::GetDrawGraphData(int handle, float xRatio, float yRatio)
{
	DRAW_GRAPH_DATA drawData;
	drawData.drawType = DRAW_GRAPH_TYPE::NORMAL;
	if (handle != -1)
	{
		drawData.handle = handle;
	}
	drawData.transFlag = TRUE;

	drawData.pos = mstDisplaySize.LeftUp_Ratio(Vector2(yRatio, yRatio));

	return drawData;
}

// 描画情報取得
DRAW_GRAPH_DATA ResourceManager::GetDrawGraphData(int handle, float xRatio, float yRatio, int sizeX, int sizeY)
{
	DRAW_GRAPH_DATA drawData;
	drawData.drawType = DRAW_GRAPH_TYPE::SIZE;
	if (handle != -1)
	{
		drawData.handle = handle;
	}
	drawData.transFlag = TRUE;

	drawData.pos = mstDisplaySize.LeftUp_Ratio(Vector2(yRatio, yRatio));

	drawData.size.x = sizeX;
	drawData.size.y = sizeY;

	return drawData;
}

// 描画情報取得
DRAW_GRAPH_DATA ResourceManager::GetDrawGraphData(int handle, float xRatio, float yRatio, float sizeXRatio, float sizeYRatio)
{
	DRAW_GRAPH_DATA drawData;
	drawData.drawType = DRAW_GRAPH_TYPE::SIZE;
	if (handle != -1)
	{
		drawData.handle = handle;
	}
	drawData.transFlag = TRUE;

	drawData.pos = mstDisplaySize.LeftUp_Ratio(Vector2(yRatio, yRatio));

	drawData.size = mstDisplaySize.LeftUp_Ratio(Vector2(sizeXRatio, sizeYRatio));

	return drawData;
}

// 描画情報取得
DRAW_GRAPH_DATA ResourceManager::GetDrawGraphData(int handle, Vector2_Int pos)
{
	DRAW_GRAPH_DATA drawData;
	drawData.drawType = DRAW_GRAPH_TYPE::NORMAL;
	if (handle != -1)
	{
		drawData.handle = handle;
	}
	drawData.transFlag = TRUE;

	drawData.pos = pos;

	return drawData;
}

// 描画情報取得
DRAW_GRAPH_DATA ResourceManager::GetDrawGraphData(int handle, Vector2_Int pos, Vector2_Int size)
{
	DRAW_GRAPH_DATA drawData;
	drawData.drawType = DRAW_GRAPH_TYPE::SIZE;
	if (handle != -1)
	{
		drawData.handle = handle;
	}
	drawData.transFlag = TRUE;

	drawData.pos = pos;

	drawData.size = size;

	return drawData;
}

// 描画情報取得
DRAW_GRAPH_DATA ResourceManager::GetDrawGraphData(int handle, Vector2_Int leftUp, Vector2_Int rightUp, Vector2_Int leftDown, Vector2_Int rightDown)
{
	DRAW_GRAPH_DATA drawData;
	drawData.drawType = DRAW_GRAPH_TYPE::FREE;
	if (handle != -1)
	{
		drawData.handle = handle;
	}
	drawData.transFlag = TRUE;

	drawData.upLeft = leftUp;
	drawData.upRight = rightUp;
	drawData.downLeft = leftDown;
	drawData.downRight = rightDown;

	return drawData;
}

/*------------*/
/*【3Dモデル】*/
/*------------*/
// モデルハンドル取得
int ResourceManager::GetModelHandle(std::string fileName)
{// TODO: ファイル名に"../"が必要になっているから無しでできるようにする "Resource"も
	int handle = -1;
	if (mmModelHandle.find(fileName) != mmModelHandle.end())
	{
		handle = mmModelHandle[fileName][0];
		mmModelCount[handle] += 1;
		int resultHandle = MV1DuplicateModel(handle);
		mmModelHandle[fileName].push_back(resultHandle);
		return resultHandle;
	}

	handle = MV1LoadModel(fileName.c_str());
	if (handle == -1)
	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::RESOURCE_FLAG);
		return -1;
	}
	std::vector<int> setHandle;
	setHandle.clear();
	setHandle.reserve(2);
	setHandle.push_back(handle);
	setHandle.push_back(MV1DuplicateModel(handle));
	mmModelHandle[fileName] = setHandle;
	mmModelCount[handle] = 1;

	return setHandle[1];
}

// モデルハンドル削除
void ResourceManager::ReduceModelHandle(int handle)
{
	std::string fileName = "NULL";
	for (std::pair<std::string, std::vector<int>> modelHandle : mmModelHandle)
	{
		for (int i = 0; i < modelHandle.second.size(); i++)
		{
			if (modelHandle.second[i] == handle)
			{
				fileName = modelHandle.first;
				handle = modelHandle.second[0];
				break;
			}
		}
		
		if (fileName != "NULL")
		{
			break;
		}
	}

	mmModelCount[handle] -= 1;
	if (mmModelCount[handle] <= 0)
	{
		MV1DeleteModel(handle);
		mmModelCount.erase(handle);
		mmModelHandle.erase(fileName);
	}
}


/*--------*/
/*【画像】*/
/*--------*/
// 画像ハンドル取得
int ResourceManager::GetGraphHandle(std::string fileName)
{
	int handle = -1;
	if (mmGraphHandle.find(fileName) != mmGraphHandle.end())
	{
		handle = mmGraphHandle[fileName];
		mmGraphCount[handle] += 1;
		return handle;
	}

	handle = LoadGraph(fileName.c_str());
	if (handle == -1)
	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::RESOURCE_FLAG);
		return -1;
	}
	mmGraphHandle[fileName] = handle;
	mmGraphCount[handle] = 1;

	return handle;
}

// 画像カウントを減らす
void ResourceManager::ReduceGraphHandle(int handle)
{
	mmGraphCount[handle] -= 1;
	if (mmGraphCount[handle] <= 0)
	{
		DeleteGraph(handle);
		mmGraphCount.erase(handle);

		std::string fileName;
		for (std::pair<std::string, int> graphHandle : mmGraphHandle)
		{
			if (graphHandle.second == handle)
			{
				fileName = graphHandle.first;
				break;
			}
		}
		mmGraphHandle.erase(fileName);
	}
}

// Div画像ハンドル取得
void ResourceManager::GetDivGraphHandle(std::string fileName, DIV_GRAPH_DATA* graphData)
{
	if (mmGraphHandle.find(fileName) != mmGraphHandle.end())
	{
		*graphData = mmDivGraphHandle[fileName];
		graphData->count += 1;
		return;
	}


	if (LoadDivGraph(fileName.c_str(), graphData->allNum, graphData->xNum, graphData->yNum, graphData->xSize, graphData->ySize, graphData->handle) == -1)
	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::RESOURCE_FLAG);
		return;
	}
	mmDivGraphHandle[fileName] = *graphData;
	msDivGraphFileNames.push_back(fileName);
	graphData->count += 1;
	graphData->number = ((int)msDivGraphFileNames.size() - 1);
}

// Div画像カウントを減らす
void ResourceManager::ReduceDivGraphHandle(int number)
{
	if ((mmDivGraphHandle[msDivGraphFileNames[number]].count -= 1) <= 0)
	{
		for (int i = 0; i < mmDivGraphHandle[msDivGraphFileNames[number]].allNum; i++)
		{
			DeleteGraph(*(mmDivGraphHandle[msDivGraphFileNames[number]].handle + i));
		}
		mmDivGraphHandle.erase(msDivGraphFileNames[number]);
		msDivGraphFileNames.erase(msDivGraphFileNames.begin() + number);
	}
}


/*--------*/
/*【動画】*/
/*--------*/
// 動画ハンドル取得
int ResourceManager::GetMovieHandle(std::string fileName)
{
	int handle = -1;
	if (mmMovieHandle.find(fileName) != mmMovieHandle.end())
	{
		handle = mmMovieHandle[fileName];
		mmMovieCount[handle] += 1;
		return handle;
	}

	handle = LoadGraph(fileName.c_str());
	if (handle == -1)
	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::RESOURCE_FLAG);
		return -1;
	}
	mmMovieHandle[fileName] = handle;
	mmMovieCount[handle] = 1;

	return handle;
}

// 動画カウントを減らす
void ResourceManager::ReduceMovie(int handle)
{
	mmMovieCount[handle] -= 1;
	if (mmMovieCount[handle] <= 0)
	{
		DeleteGraph(handle);
		mmMovieCount.erase(handle);

		std::string fileName;
		for (std::pair<std::string, int> graphHandle : mmMovieHandle)
		{
			if (graphHandle.second == handle)
			{
				fileName = graphHandle.first;
				break;
			}
		}
		mmMovieHandle.erase(fileName);
	}
}

// 動画再生
void ResourceManager::PlayMovie(int handle)
{
	PlayMovieToGraph(handle);
}

// 動画停止
void ResourceManager::StopMovie(int handle)
{
	PauseMovieToGraph(handle);
}

// 動画リセット
void ResourceManager::MovieReset(int handle)
{
	SeekMovieToGraph(handle, 0);
}

// 動画ループ
void ResourceManager::MovieLoop(int handle)
{
	if (GetMovieStateToGraph(handle) != 1)
	{
		MovieReset(handle);
		PlayMovie(handle);
	}
}

/*------------*/
/*【サウンド】*/
/*------------*/



/*----------*/
/*【エフェクト】
/*----------*/

// エフェクト情報取得
int ResourceManager::GetEffectResource(std::string fileName, float size)
{
	int handle = -1;
	if (mmEffectHandle.find(fileName) != mmEffectHandle.end())
	{
		handle = mmEffectHandle[fileName][0];
		mmEffectCount[handle] += 1;
		return handle;
	}

	handle = LoadEffekseerEffect(fileName.c_str(), size);
	if (handle == -1)
	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::RESOURCE_FLAG);
		return -1;
	}
	std::vector<int> setHandle;
	setHandle.clear();
	setHandle.push_back(handle);
	mmEffectHandle[fileName] = setHandle;
	mmEffectCount[handle] = 1;

	return handle;
}

// エフェクトハンドルを取得する
int ResourceManager::GetEffectHandle(int handle, int oldHandle)
{
	for (std::pair<std::string, std::vector<int>> effectHandle : mmEffectHandle)
	{
		if (effectHandle.second[0] == handle)
		{
			int newHandle = PlayEffekseer3DEffect(effectHandle.second[0]);
			if (newHandle == -1)
			{
				Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::RESOURCE_FLAG);
				return -1;
			}
			
			if (oldHandle != -1)
			{
				for (int i = 1; i < effectHandle.second.size(); i++)
				{
					if (effectHandle.second[i] == oldHandle)
					{
						mmEffectHandle[effectHandle.first][i] = newHandle;
					}
				}
			}
			else
			{
				mmEffectHandle[effectHandle.first].push_back(newHandle);
			}

			return newHandle;
		}
	}

	return -1;
}

// エフェクトカウントを減らす
void ResourceManager::ReduceEffect(int handle)
{
	std::string fileName = "NULL";
	for (std::pair<std::string, std::vector<int>> effectHandle : mmEffectHandle)
	{
		for (int i = 0; i < effectHandle.second.size(); i++)
		{
			if (effectHandle.second[i] == handle)
			{
				fileName = effectHandle.first;
				handle = effectHandle.second[0];
				break;
			}
		}
		
		if (fileName != "NULL")
		{
			break;
		}
	}

	mmEffectCount[handle] -= 1;
	if (mmEffectCount[handle] <= 0)
	{
		DeleteEffekseerEffect(handle);
		mmEffectCount.erase(handle);
		mmEffectHandle.erase(fileName);
	}
}

// エフェクト描画
void ResourceManager::DrawEffect(int handle, VECTOR position, VECTOR angle, VECTOR size)
{
	if (!mbEffectDrawFlag)
	{
		DrawGraph(0, 0, mnEffectDrawPreHandle, TRUE);
		mbEffectDrawFlag = true;
	}

	SetPosPlayingEffekseer3DEffect(handle, position.x, position.y, position.z);
	SetRotationPlayingEffekseer3DEffect(handle, angle.x, angle.y, angle.z);
	SetScalePlayingEffekseer3DEffect(handle, size.x, size.y, size.z);
}

// エフェクト停止
void ResourceManager::StopEffect(int handle)
{
	SetSpeedPlayingEffekseer3DEffect(handle, 0.0f);
}

// エフェクト再生
void ResourceManager::PlayEffect(int handle, float speed)
{
	SetSpeedPlayingEffekseer3DEffect(handle, speed);
}

// エフェクト初期化
void ResourceManager::EffectInit()
{
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effekseer_Init(20000 * 10) == -1)//8000) == -1)
	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::RESOURCE_FLAG);
		return;
	}
	
	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Zバッファを有効にする。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	SetWriteZBuffer3D(TRUE);

	// エフェクト描画用画像取得
	mnEffectDrawPreHandle = GetGraphHandle("../Resource/Effect/Background.png");
}

// エフェクト終了
void ResourceManager::EffectFinailize()
{
    for (auto &handle : mmEffectHandle)
    {
        DeleteEffekseerEffect(handle.second[0]);
    }

    mmEffectHandle.clear();
    mmEffectHandle.clear();
    Effkseer_End();
}

// エフェクト描画処理
void ResourceManager::EffectDrawProcess()
{
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();
}