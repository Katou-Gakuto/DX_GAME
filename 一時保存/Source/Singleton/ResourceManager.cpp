#include <map>
#include <string>
#include <vector>

#include "ResourceEnum.h"
#include "ResourceData.h"
#include "Vector2.h"

#include "DxLib.h"
#include "EffekseerForDXLib.h"

#include "Master.h"

#include "DataManager.h"
#include "EndManager.h"
#include "HandleContainer.h"
#include "ResourceManager.h"

#ifdef _DEBUG
#include "DebugLogs/DebugLog.h"
#endif

std::string ResourceManager::msResourceFile = "Resource/";
DisplaySize ResourceManager::mstDisplaySize = DisplaySize();
/*--------*/
/*【共通】*/
/*--------*/
ResourceManager::ResourceManager()
: mbEffectDrawFlag(false)
, mnEffectDrawPreHandle(-1)
, mp3DModelHandleContainer(nullptr)
, mpGraphHandleContainer(nullptr)
, mpMovieHandleContainer(nullptr)
, mpSoundHandleContainer(nullptr)
, mpPlaySoundHandleContainer(nullptr)
, mp3DSoundHandleContainer(nullptr)
, mpPlay3DSoundHandleContainer(nullptr)
, mnPlayBackSoundHandle(-1)
, mpEffectHandleContainer(nullptr)
, mbDrawShadowMapFlag(false)
, mpDataManager(nullptr)
{
	// シャドウマップ
	mnShadowMapHandle = -1;

	// 3Dモデル
	// mmModelHandle.clear();
	// mmModelCount.clear();

	// 画像
	// mmGraphHandle.clear();
	// mmGraphCount.clear();
	mmDivGraphHandle.clear();
	msDivGraphFileNames.clear();

	// エフェクト
	// mmEffectHandle.clear();
	// mmEffectCount.clear();
}
ResourceManager::~ResourceManager()
{
}

// 初期化
void ResourceManager::Initilize()
{
	// 3Dモデル
	mp3DModelHandleContainer = new HandleContainer<std::string>();

	// 画像
	mpGraphHandleContainer = new HandleContainer<std::string>();
	mpGraphHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_LOOK);

	// 動画
	mpMovieHandleContainer = new HandleContainer<std::string>();
	mpMovieHandleContainer->SetHandleFlag(HANDLE_FLAG::NONE);

	// サウンド
	mpDataManager = Master::mpDataManager;
	mpSoundHandleContainer = new HandleContainer<std::string>();
	mpSoundHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_LOOK);
	mpPlaySoundHandleContainer = new HandleContainer<int>();
	mpPlaySoundHandleContainer->SetHandleFlag(HANDLE_FLAG::NONE);

	mp3DSoundHandleContainer = new HandleContainer<std::string>();
	mp3DSoundHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_LOOK);
	mpPlay3DSoundHandleContainer = new HandleContainer<int>();
	mpPlay3DSoundHandleContainer->SetHandleFlag(HANDLE_FLAG::NONE);

	// エフェクト
	mpEffectHandleContainer = new HandleContainer<std::string>();

	// ディスプレイサイズ設定
	Vector2_Int setDisplaySize;
    GetScreenState(&setDisplaySize.x, &setDisplaySize.y, &mstDisplaySize.colorBit);
	mstDisplaySize = setDisplaySize;

	// 明るさ
	SetGlobalAmbientLight(GetColorF(0.3f, 0.3f, 0.3f, 1.0f));

	ShadowMapInit();

	EffectInit();
}

// 終了
void ResourceManager::Finalize()
{
	{// シャドウマップ
		DeleteShadowMap(mnShadowMapHandle);
	}

	{// 3Dモデル
		MV1InitModel();
		// mmModelCount.clear();
		// mmModelHandle.clear();

		delete mp3DModelHandleContainer;
	}

	{// 画像
		for (std::pair<std::string, std::vector<int>> graphHandle : mpGraphHandleContainer->GetHandleMap())
		{
			for (int i = 0; i < graphHandle.second.size(); i++)
			{
				DeleteGraph(graphHandle.second[i]);
#ifdef _DEBUG
				DEBUG::SaveText("画像ハンドル削除(最終) : " + std::to_string(graphHandle.second[i]) + " : " + graphHandle.first + " : HandleNumber <=" + std::to_string(mpGraphHandleContainer->GetHandleCount(graphHandle.second[i])) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_GRAPH);
#endif
			}
		}
		// mmGraphHandle.clear();
		// mmGraphCount.clear();

		delete mpGraphHandleContainer;

		for (const std::pair<std::string, DIV_GRAPH_DATA>& divHandle : mmDivGraphHandle)
		{
			for (int i = 0; i < divHandle.second.allNum; i++)
			{
				DeleteGraph(*(divHandle.second.handle + i));
#ifdef _DEBUG
				DEBUG::SaveText("DIV画像ハンドル削除(最終) : " + std::to_string(*(divHandle.second.handle + i)) + '\n');
#endif
			}
		}
		mmDivGraphHandle.clear();
		msDivGraphFileNames.clear();
	}

	{// 動画
		for (std::pair<std::string, std::vector<int>> moveiHandle : mpMovieHandleContainer->GetHandleMap())
		{
			for (int i = 0; i < moveiHandle.second.size(); i++)
			{
				DeleteGraph(moveiHandle.second[i]);
#ifdef _DEBUG
				DEBUG::SaveText("動画ハンドル削除(最終) : " + std::to_string(moveiHandle.second[i]) + " : " + moveiHandle.first + " : HandleNumber <=" + std::to_string(mpMovieHandleContainer->GetHandleCount(moveiHandle.second[i])) + '\n');
#endif
			}
		}
		delete mpMovieHandleContainer;
	}

	{// サウンド
		for (std::pair<std::string, std::vector<int>> soundHandle : mpSoundHandleContainer->GetHandleMap())
		{
			for (int i = 0; i < soundHandle.second.size(); i++)
			{
				DeleteSoundMem(soundHandle.second[i]);
#ifdef _DEBUG
				DEBUG::SaveText("サウンド(原本)ハンドル削除(最終) : " + std::to_string(soundHandle.second[i]) + " : " + soundHandle.first + " : HandleNumber <=" + std::to_string(mpSoundHandleContainer->GetHandleCount(soundHandle.second[i])) + '\n');
#endif
			}
		}
		delete mpSoundHandleContainer;

		for (std::pair<int, std::vector<int>> playSoundHandle : mpPlaySoundHandleContainer->GetHandleMap())
		{
			for (int i = 0; i < playSoundHandle.second.size(); i++)
			{
				DeleteSoundMem(playSoundHandle.second[i]);
#ifdef _DEBUG
				DEBUG::SaveText("サウンドハンドル削除(最終) : " + std::to_string(playSoundHandle.second[i]) + " : " + std::to_string(playSoundHandle.first) + " : HandleNumber <=" + std::to_string(mpPlaySoundHandleContainer->GetHandleCount(playSoundHandle.second[i])) + '\n');
#endif
			}
		}
		delete mpPlaySoundHandleContainer;

		for (std::pair<std::string, std::vector<int>> sound3DHandle : mp3DSoundHandleContainer->GetHandleMap())
		{
			for (int i = 0; i < sound3DHandle.second.size(); i++)
			{
				DeleteSoundMem(sound3DHandle.second[i]);
#ifdef _DEBUG
				DEBUG::SaveText("3Dサウンド(原本)ハンドル削除(最終) : " + std::to_string(sound3DHandle.second[i]) + " : " + sound3DHandle.first + " : HandleNumber <=" + std::to_string(mp3DSoundHandleContainer->GetHandleCount(sound3DHandle.second[i])) + '\n');
#endif
			}
		}
		delete mp3DSoundHandleContainer;

		for (std::pair<int, std::vector<int>> playSound3DHandle : mpPlay3DSoundHandleContainer->GetHandleMap())
		{
			for (int i = 0; i < playSound3DHandle.second.size(); i++)
			{
				DeleteSoundMem(playSound3DHandle.second[i]);
#ifdef _DEBUG
				DEBUG::SaveText("3Dサウンドハンドル削除(最終) : " + std::to_string(playSound3DHandle.second[i]) + " : " + std::to_string(playSound3DHandle.first) + " : HandleNumber <=" + std::to_string(mpPlay3DSoundHandleContainer->GetHandleCount(playSound3DHandle.second[i])) + '\n');
#endif
			}
		}
		delete mpPlay3DSoundHandleContainer;
	}

	{// エフェクト
		EffectFinalize();
	}
}

// 更新
void ResourceManager::Update()
{
	// サウンドボリュームの更新
	SoundUpdate();
}

// 開始描画
void ResourceManager::StartDraw()
{
	// シャドウマップへの描画の準備
	ShadowMap_DrawSetup(mnShadowMapHandle);
	mbDrawShadowMapFlag = true;
}
// 中間描画
void ResourceManager::MiddleDraw()
{
	// シャドウマップへの描画を終了
	ShadowMap_DrawEnd();
	mbDrawShadowMapFlag = false;
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

	case DRAW_GRAPH_TYPE::RECT_EXTEND:
		failureFlag = DrawRectExtendGraph(drawData.pos.x, drawData.pos.y, drawData.extPos.x, drawData.extPos.y, drawData.graphPos.x, drawData.graphPos.y, drawData.graphSize.x, drawData.graphSize.y, drawData.handle, drawData.transFlag);
		break;

	case DRAW_GRAPH_TYPE::RECT_EXTEND_SIZE:
		failureFlag = DrawRectExtendGraph(drawData.pos.x, drawData.pos.y, drawData.pos.x + drawData.size.x, drawData.pos.y + drawData.size.y, drawData.graphPos.x, drawData.graphPos.y, drawData.graphSize.x, drawData.graphSize.y, drawData.handle, drawData.transFlag);
		break;
	}
}

// シャドウマップの初期化
void ResourceManager::ShadowMapInit()
{
	// シャドウマップハンドル作成
	mnShadowMapHandle = MakeShadowMap(4096, 4096);
	// シャドウマップが想定するライトの方向もセット
	SetShadowMapLightDirection(mnShadowMapHandle, VGet( 0.5f, -0.5f, 0.5f));

	// シャドウマップに描画する範囲を設定
	SetShadowMapDrawArea(mnShadowMapHandle, VGet(-400.0f, -1.0f, -400.0f), VGet(10000.0f, 10000.0f, 10000.0f));
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

	drawData.pos = mstDisplaySize.LeftUp_Ratio(Vector2(xRatio, yRatio));

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

	drawData.pos = mstDisplaySize.LeftUp_Ratio(Vector2(xRatio, yRatio));

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

	drawData.pos = mstDisplaySize.LeftUp_Ratio(Vector2(xRatio, yRatio));

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
{
	int handle = -1;
	if (mp3DModelHandleContainer->CheckFileName(fileName))
	{
		handle = mp3DModelHandleContainer->GetHandles(fileName)[0];

		mp3DModelHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_EXCEPT_LOOK);
#ifdef _DEBUG
		int resultHandle = mp3DModelHandleContainer->RegisterHandle(MV1DuplicateModel(handle));
		DEBUG::SaveText("モデルハンドル取得 : " + fileName + " : " + std::to_string(resultHandle) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_3D_MODEL);
		return resultHandle;
#endif
		return mp3DModelHandleContainer->RegisterHandle(MV1DuplicateModel(handle));
	}

		
	mp3DModelHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_LOOK);
	handle = mp3DModelHandleContainer->RegisterHandle(MV1LoadModel(fileName.c_str()), false);
#ifdef _DEBUG
		DEBUG::SaveText("モデルハンドル(原本)取得 : " + fileName + " : " + std::to_string(handle) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_3D_MODEL);
#endif
	
	mp3DModelHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_EXCEPT_LOOK);
#ifdef _DEBUG
	handle = mp3DModelHandleContainer->RegisterHandle(MV1DuplicateModel(handle));
	DEBUG::SaveText("モデルハンドル(一つ目)取得 : " + fileName + " : " + std::to_string(handle) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_3D_MODEL);
	return handle;
#endif
	return mp3DModelHandleContainer->RegisterHandle(MV1DuplicateModel(handle));
}

// モデルハンドル削除
void ResourceManager::ReduceModelHandle(int handle)
{
	mp3DModelHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_EXCEPT_LOOK);
	std::vector<int> deleteHnadle = mp3DModelHandleContainer->DeleteHandle(handle);

	#ifdef _DEBUG
	std::string text = "モデルハンドル削除 : " + std::to_string(handle) + "(NOT_DELETE)";
	for (int i = 0; i < deleteHnadle.size(); i++)
	{
		text = text + " : " + std::to_string(deleteHnadle[i]);
	}
	text = text + '\n';
	DEBUG::SaveText(text, DEBUG::DEBUG_MAP_TYPE::DEBUG_3D_MODEL);
	#endif

	for (int i = 0; i < deleteHnadle.size(); i++)
	{
		MV1DeleteModel(deleteHnadle[i]);
	}

	// std::string fileName = "NULL";
	// for (std::pair<std::string, std::vector<int>> modelHandle : mp3DModelHandleContainer->GetHandleMap())
	// {
	// 	for (int i = 0; i < modelHandle.second.size(); i++)
	// 	{
	// 		if (modelHandle.second[i] == handle)
	// 		{
	// 			fileName = modelHandle.first;
	// 			handle = modelHandle.second[0];
	// 			break;
	// 		}
	// 	}

	// 	if (fileName != "NULL")
	// 	{
	// 		break;
	// 	}
	// }

	// mmModelCount[handle] -= 1;
	// if (mmModelCount[handle] <= 0)
	// {
	// 	MV1DeleteModel(handle);
	// 	mmModelCount.erase(handle);
	// 	mmModelHandle.erase(fileName);
	// }
}


/*--------*/
/*【画像】*/
/*--------*/
// 画像ハンドル取得
int ResourceManager::GetGraphHandle(std::string fileName)
{
	if (mpGraphHandleContainer->CheckFileName(fileName))
	{
#ifdef _DEBUG
		int resultHandle = mpGraphHandleContainer->RegisterHandle(0);
		DEBUG::SaveText("画像ハンドル取得 : " + fileName + " : " + std::to_string(resultHandle) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_GRAPH);
		return resultHandle;
#endif
		return mpGraphHandleContainer->RegisterHandle(0/*何も指定しない*/);
	}

#ifdef _DEBUG
	int handle = mpGraphHandleContainer->RegisterHandle(LoadGraph(fileName.c_str()));
	DEBUG::SaveText("画像ハンドル(原本)取得 : " + fileName + " : " + std::to_string(handle) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_GRAPH);
	return handle;
#endif
	return mpGraphHandleContainer->RegisterHandle(LoadGraph(fileName.c_str()));
}

// 画像カウントを減らす
void ResourceManager::ReduceGraphHandle(int handle)
{
	std::vector<int> deleteHandle = mpGraphHandleContainer->DeleteHandle(handle);
	
	#ifdef _DEBUG
	std::string text = "画像ハンドル削除 : " + std::to_string(handle) + "(NOT_DELETE)";
	for (int i = 0; i < deleteHandle.size(); i++)
	{
		text = text + " : " + std::to_string(deleteHandle[i]);
	}
	text = text + '\n';
	DEBUG::SaveText(text, DEBUG::DEBUG_MAP_TYPE::DEBUG_GRAPH);
	#endif

	for (int i = 0; i < deleteHandle.size(); i++)
	{
		DeleteGraph(deleteHandle[i]);
	}

	// mmGraphCount[handle] -= 1;
	// if (mmGraphCount[handle] <= 0)
	// {
	// 	DeleteGraph(handle);
	// 	mmGraphCount.erase(handle);

	// 	std::string fileName;
	// 	for (std::pair<std::string, int> graphHandle : mmGraphHandle)
	// 	{
	// 		if (graphHandle.second == handle)
	// 		{
	// 			fileName = graphHandle.first;
	// 			break;
	// 		}
	// 	}
	// 	mmGraphHandle.erase(fileName);
	// }
}

// Div画像ハンドル取得
void ResourceManager::GetDivGraphHandle(std::string fileName, DIV_GRAPH_DATA* graphData)
{
	if (mmDivGraphHandle.find(fileName) != mmDivGraphHandle.end())
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

#ifdef _DEBUG
	int handle = mpMovieHandleContainer->RegisterHandle(LoadGraph(fileName.c_str()), fileName);
	DEBUG::SaveText("動画ハンドル取得 : " + fileName + " : " + std::to_string(handle) + '\n');
	return handle;
#endif
	return mpMovieHandleContainer->RegisterHandle(LoadGraph(fileName.c_str()), fileName);
	// int handle = -1;
	// if (mpMovieHandleContainer->CheckFileName(fileName))
	// {
	// 	return mpMovieHandleContainer->RegisterHandle(LoadGraph(fileName.c_str()));
	// }

	// handle = LoadGraph(fileName.c_str());
	// if (handle == -1)
	// {
	// 	Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::RESOURCE_FLAG);
	// 	return -1;
	// }
	// std::vector<int> setHandle;
	// setHandle.clear();
	// setHandle.push_back(handle);
	// mmMovieHandle[fileName] = setHandle;
}

// 動画カウントを減らす
void ResourceManager::ReduceMovie(int handle)
{
	std::vector<int> deleteHandle =  mpMovieHandleContainer->DeleteHandle(handle);
	
	#ifdef _DEBUG
	std::string text = "動画ハンドル削除 : " + std::to_string(handle) + "(NOT_DELETE)";
	for (int i = 0; i < deleteHandle.size(); i++)
	{
		text = text + " : " + std::to_string(deleteHandle[i]);
	}
	text = text + '\n';
	DEBUG::SaveText(text);
	#endif

	for (int i = 0; i < deleteHandle.size(); i++)
	{
		DeleteGraph(deleteHandle[i]);
	}

	// DeleteGraph(handle);

	// for (auto movieHandle : mmMovieHandle)
	// {
	// 	for (int i = 0; i < movieHandle.second.size(); i++)
	// 	{
	// 		if (movieHandle.second[i] == handle)
	// 		{
	// 			if ((movieHandle.second.size() - 1) <= 0)
	// 			{
	// 				mmMovieHandle.erase(movieHandle.first);
	// 			}
	// 			else
	// 			{
	// 				mmMovieHandle[movieHandle.first].erase(mmMovieHandle[movieHandle.first].begin() + i);
	// 			}
	// 			return;
	// 		}
	// 	}
	// }
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

// サウンドハンドル取得
int ResourceManager::GetSoundHandle(std::string fileName)
{
	if (mpSoundHandleContainer->CheckFileName(fileName))
	{
		return mpSoundHandleContainer->RegisterHandle(0/*何も指定しない*/);
	}

#ifdef _DEBUG
	int handle = mpSoundHandleContainer->RegisterHandle(LoadSoundMem(fileName.c_str()));
	DEBUG::SaveText("サウンドハンドル(原本)取得 : " + fileName + " : " + std::to_string(handle) + '\n');
	return handle;
#endif
	return mpSoundHandleContainer->RegisterHandle(LoadSoundMem(fileName.c_str()));
}

// サウンドカウントを減らす
void ResourceManager::ReduceSoundHandle(int handle)
{
	std::vector<int> deleteHandle =  mpSoundHandleContainer->DeleteHandle(handle);
	
	#ifdef _DEBUG
	std::string text = "サウンドハンドル削除 : " + std::to_string(handle) + "(NOT_DELETE)";
	for (int i = 0; i < deleteHandle.size(); i++)
	{
		text = text + " : " + std::to_string(deleteHandle[i]);
	}
	text = text + '\n';
	DEBUG::SaveText(text);
	#endif

	for (int i = 0; i < deleteHandle.size(); i++)
	{
		DeleteSoundMem(deleteHandle[i]);
	}
}

// 3Dサウンドハンドル取得
int ResourceManager::Get3DSoundHandle(std::string fileName)
{
	if (mp3DSoundHandleContainer->CheckFileName(fileName))
	{
		return mp3DSoundHandleContainer->RegisterHandle(0/*何も指定しない*/);
	}

	int handle = mp3DSoundHandleContainer->RegisterHandle(LoadSoundMem(fileName.c_str()));
#ifdef _DEBUG
	DEBUG::SaveText("3Dサウンドハンドル(原本)取得 : " + fileName + " : " + std::to_string(handle) + '\n');
#endif
	return handle;
}

// 3Dサウンドカウントを減らす
void ResourceManager::Reduce3DSoundHandle(int handle)
{
	std::vector<int> deleteHandle =  mp3DSoundHandleContainer->DeleteHandle(handle);
	
	#ifdef _DEBUG
	std::string text = "3Dサウンドハンドル削除 : " + std::to_string(handle) + "(NOT_DELETE)";
	for (int i = 0; i < deleteHandle.size(); i++)
	{
		text = text + " : " + std::to_string(deleteHandle[i]);
	}
	text = text + '\n';
	DEBUG::SaveText(text);
	#endif

	for (int i = 0; i < deleteHandle.size(); i++)
	{
		DeleteSoundMem(deleteHandle[i]);
	}
}

// バックグラウンドハンドル設定
void ResourceManager::SetBackSoundHandle(int handle)
{
	if (mnPlayBackSoundHandle != -1)
	{
		StopSoundMem(mnPlayBackSoundHandle);
		DeleteSoundMem(mnPlayBackSoundHandle);
	}
	
	int backSoundHandle = DuplicateSoundMem(handle);

	ChangeVolumeSoundMem(mnBackSoundVolume, backSoundHandle);

	PlaySoundMem(backSoundHandle, DX_PLAYTYPE_LOOP, TRUE);

	mnPlayBackSoundHandle = backSoundHandle;
}

// サウンド更新
void ResourceManager::SoundUpdate()
{
	std::map<int, std::vector<int>>* playSoundHandleMap = mpPlaySoundHandleContainer->GetHandleMapPointer();
	std::map<int, std::vector<int>>* play3DSoundHandleMap = mpPlay3DSoundHandleContainer->GetHandleMapPointer();

	// 音量確認
	{
		if (mpDataManager->GetSeVolume() != mnSoundVolume)
		{
			mnSoundVolume = mpDataManager->GetSeVolume();
			for (std::pair<const int, std::vector<int>>& playSoundHandle : *playSoundHandleMap)
			{
				for (int i = 0; i < playSoundHandle.second.size(); i++)
				{
					ChangeVolumeSoundMem(mnSoundVolume, playSoundHandle.second[i]);
				}
			}
			for (std::pair<const int, std::vector<int>>& play3DSoundHandle : *play3DSoundHandleMap)
			{
				for (int i = 0; i < play3DSoundHandle.second.size(); i++)
				{
					ChangeVolumeSoundMem(mnSoundVolume, play3DSoundHandle.second[i]);
				}
			}
		}

		if (mpDataManager->GetBgmVolume() != mnBackSoundVolume)
		{
			mnBackSoundVolume = mpDataManager->GetBgmVolume();
			if (mnPlayBackSoundHandle != -1)
			{
				ChangeVolumeSoundMem(mnBackSoundVolume, mnPlayBackSoundHandle);
			}
		}
	}

	for (std::pair<int, std::vector<int>> playSoundHandle : *playSoundHandleMap)
	{
		for (int i = 0; i < playSoundHandle.second.size(); i++)
		{
			if (CheckSoundMem(playSoundHandle.second[i]) == 0)
			{
				StopSoundMem(playSoundHandle.second[i]);
				std::vector<int> deleteHandle = mpPlaySoundHandleContainer->DeleteHandle(playSoundHandle.second[i]);
	
	#ifdef _DEBUG
	std::string text = "プレイサウンドハンドル削除 : " + std::to_string(playSoundHandle.second[i]) + "(NOT_DELETE)";
	for (int i = 0; i < deleteHandle.size(); i++)
	{
		text = text + " : " + std::to_string(deleteHandle[i]);
	}
	text = text + '\n';
	DEBUG::SaveText(text);
	#endif
				DeleteSoundMem(playSoundHandle.second[i]);
			}
		}
	}
	for (std::pair<int, std::vector<int>> play3DSoundHandle : *play3DSoundHandleMap)
	{
		for (int i = 0; i < play3DSoundHandle.second.size(); i++)
		{
			if (CheckSoundMem(play3DSoundHandle.second[i]) == 0)
			{
				StopSoundMem(play3DSoundHandle.second[i]);
				std::vector<int> deleteHandle = mpPlay3DSoundHandleContainer->DeleteHandle(play3DSoundHandle.second[i]);
	
	#ifdef _DEBUG
	std::string text = "プレイ3Dサウンドハンドル削除 : " + std::to_string(play3DSoundHandle.second[i]) + "(NOT_DELETE)";
	for (int i = 0; i < deleteHandle.size(); i++)
	{
		text = text + " : " + std::to_string(deleteHandle[i]);
	}
	text = text + '\n';
	DEBUG::SaveText(text);
	#endif
				DeleteSoundMem(play3DSoundHandle.second[i]);
			}
		}
	}
}

// サウンド再生設定
void ResourceManager::SetPlaySound(int handle, int volume)
{
	int soundHandle = mpPlaySoundHandleContainer->RegisterHandle(DuplicateSoundMem(handle), handle);
#ifdef _DEBUG
	DEBUG::SaveText((std::string)"サウンドハンドル取得 : " + (std::string)"なし" + (std::string)" : " + std::to_string(soundHandle) + '\n');
#endif

	ChangeVolumeSoundMem(mnSoundVolume, soundHandle);

	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK, TRUE);
}

// 3Dサウンド再生設定
void ResourceManager::SetPlay3DSound(int handle, VECTOR position, int volume)
{
	SetCreate3DSoundFlag(TRUE);	

	int soundHandle = mpPlay3DSoundHandleContainer->RegisterHandle(DuplicateSoundMem(handle), handle);
#ifdef _DEBUG
	DEBUG::SaveText((std::string)"3Dサウンドハンドル取得 : " + (std::string)"なし" + (std::string)" : " + std::to_string(soundHandle) + '\n');
#endif

	Set3DPositionSoundMem(position, soundHandle);
	Set3DRadiusSoundMem(2000.0f, soundHandle);

	ChangeVolumeSoundMem(mnSoundVolume, soundHandle);

	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK, TRUE);
	
	SetCreate3DSoundFlag(FALSE);
}

/*----------*/
/*【エフェクト】
/*----------*/

// エフェクト情報取得
int ResourceManager::GetEffectResource(std::string fileName, float size)
{
	mpEffectHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_LOOK);
	
	if (mpEffectHandleContainer->CheckFileName(fileName))
	{
#ifdef _DEBUG
		int resultHandle = mpEffectHandleContainer->RegisterHandle(0);
		DEBUG::SaveText("エフェクトハンドル取得 : " + fileName + "; HANDLE : " + std::to_string(resultHandle) + "; HANDLE(原本) : " + std::to_string(mpEffectHandleContainer->GetHandleMap()[fileName][0]) + "; COUNT : " + std::to_string(mpEffectHandleContainer->GetHandleCount(mpEffectHandleContainer->GetHandleMap()[fileName][0])) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
		return resultHandle;
#endif
		return mpEffectHandleContainer->RegisterHandle(0/*何も指定しない*/);
	}

#ifdef _DEBUG
	int handle = mpEffectHandleContainer->RegisterHandle(LoadEffekseerEffect(fileName.c_str(), size));
	DEBUG::SaveText("エフェクトハンドル(原本)取得 : " + fileName + "; HANDLE : " + std::to_string(handle) + "; COUNT : " + std::to_string(mpEffectHandleContainer->GetHandleCount(mpEffectHandleContainer->GetHandleMap()[fileName][0])) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
	return handle;
#endif
	return mpEffectHandleContainer->RegisterHandle(LoadEffekseerEffect(fileName.c_str(), size));
	// if (handle == -1)
	// {
	// 	Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::RESOURCE_FLAG);
	// 	return -1;
	// }
	// std::vector<int> setHandle;
	// setHandle.clear();
	// setHandle.push_back(handle);
	// mmEffectHandle[fileName] = setHandle;
	// mmEffectCount[handle] = 1;

	// return handle;
}

// エフェクトハンドルを取得する
int ResourceManager::GetEffectHandle(int handle, int oldHandle)
{
	mpEffectHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_EXCEPT_LOOK);

	for (std::pair<std::string, std::vector<int>> effectHandle : mpEffectHandleContainer->GetHandleMap())
	{
		if (effectHandle.second[0] == handle)
		{
			if (oldHandle != -1)
			{
				// for (int i = 1; i < effectHandle.second.size(); i++)
				// {
				// 	if (effectHandle.second[i] == oldHandle)
				// 	{
				// 		StopEffekseer3DEffect(oldHandle);
				// 		mmEffectHandle[effectHandle.first][i] = newHandle;
				// 	}
				// }
				// TODO: 交換する処理に変更
				// 交換する
				std::vector<int> deleteHandle = mpEffectHandleContainer->DeleteHandle(oldHandle, false);
	
#ifdef _DEBUG
	std::string text = "オルドエフェクトハンドル削除 : " + std::to_string(oldHandle) + "(NOT_DELETE)";
	for (int i = 0; i < deleteHandle.size(); i++)
	{
		text = text + " : " + std::to_string(deleteHandle[i]);
	}
	text = text + '\n';
	DEBUG::SaveText(text);
#endif

#ifdef _DEBUG
	handle = mpEffectHandleContainer->RegisterHandle(PlayEffekseer3DEffect(handle), effectHandle.first, false);
	DEBUG::SaveText("エフェクトハンドル(交換)取得 : " + std::to_string(handle) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
	return handle;
#endif
				return mpEffectHandleContainer->RegisterHandle(PlayEffekseer3DEffect(handle), effectHandle.first, false);
			}
			else
			{
#ifdef _DEBUG
	handle = mpEffectHandleContainer->RegisterHandle(PlayEffekseer3DEffect(handle), effectHandle.first, false);
	DEBUG::SaveText("エフェクトプレイハンドル取得 : " + std::to_string(handle) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
	return handle;
#endif
				return mpEffectHandleContainer->RegisterHandle(PlayEffekseer3DEffect(handle), effectHandle.first, false);
			}
		}
	}

	return -1;
}

// 再生中エフェクトハンドルを削除する
void ResourceManager::DeletePlayEffectHandle(int handle)
{

	mpEffectHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_EXCEPT_LOOK);
	std::vector<int> deleteHandle = mpEffectHandleContainer->DeleteHandle(handle, false);
	if (deleteHandle.size() > 0)
	{
		// エフェクト削除
		StopEffekseer3DEffect(handle);
	}
#ifdef _DEBUG
	std::string text = "プレイエフェクトハンドル削除 : " + std::to_string(handle) + "(NOT_DELETE)";
	for (int i = 0; i < deleteHandle.size(); i++)
	{
		text = text + " : " + std::to_string(deleteHandle[i]);
	}
	std::map<int, int> handleCountMap = mpEffectHandleContainer->GetHandleCountMap();
	if (handleCountMap.find(handle) != handleCountMap.end())
	{
		text = text + "; COUNT : " + std::to_string(mpEffectHandleContainer->GetHandleCountMap()[handle]);
	}
	text = text + '\n';
	DEBUG::SaveText(text, DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
#endif

	// for (std::pair<std::string, std::vector<int>> effectHandle : mmEffectHandle)
	// {
	// 	for (int i = 1; i < effectHandle.second.size(); i++)
	// 	{
	// 		if (effectHandle.second[i] == handle)
	// 		{
	// 			mmEffectHandle[effectHandle.first].erase(mmEffectHandle[effectHandle.first].begin() + i);
	// 			return;
	// 		}
	// 	}
	// }
}

// エフェクトカウントを減らす
void ResourceManager::ReduceEffectDataHandle(int handle)
{
	mpEffectHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_LOOK);
	std::vector<int> deleteHandle = mpEffectHandleContainer->DeleteHandle(handle);
	
#ifdef _DEBUG
	std::string text = "エフェクトハンドル削除 : " + std::to_string(handle) + "(NOT_DELETE)";
	for (int i = 0; i < deleteHandle.size(); i++)
	{
		text = text + " : " + std::to_string(deleteHandle[i]);
	}
	text = text + '\n';
	DEBUG::SaveText(text, DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
#endif

	if (deleteHandle.size() > 0)
	{
		for (int i = 1; i < deleteHandle.size(); i++)
		{
			StopEffekseer3DEffect(deleteHandle[i]);
		}

		DeleteEffekseerEffect(deleteHandle[0]);
	}
	
	// int reduceHandle = -1;
	// std::string fileName = "NULL";
	// for (std::pair<std::string, std::vector<int>> effectHandle : mmEffectHandle)
	// {
	// 	if ((effectHandle.second.size() > 0) &&
	// 		(effectHandle.second[0] == handle))
	// 	{
	// 		fileName = effectHandle.first;
	// 		reduceHandle = effectHandle.second[0];
	// 		break;
	// 	}
	// 	// for (int i = 0; i < effectHandle.second.size(); i++)
	// 	// {
	// 	// 	if (effectHandle.second[i] == handle)
	// 	// 	{
	// 	// 		fileName = effectHandle.first;
	// 	// 		handle = effectHandle.second[0];
	// 	// 		break;
	// 	// 	}
	// 	// }

	// 	// if (fileName != "NULL")
	// 	// {
	// 	// 	break;
	// 	// }
	// }

	// if (reduceHandle == -1)
	// {
	// 	return;
	// }

	// mmEffectCount[reduceHandle] -= 1;
	// if (mmEffectCount[reduceHandle] <= 0)
	// {
	// 	DeleteEffekseerEffect(reduceHandle);
	// 	mmEffectCount.erase(reduceHandle);
	// 	mmEffectHandle.erase(fileName);
	// }
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

// 全エフェクト停止
void ResourceManager::StopAllEfect()
{
	for (std::pair<std::string, std::vector<int>> effectHandle : mpEffectHandleContainer->GetHandleMap())
	{
		for (int i = 1; i < effectHandle.second.size(); i++)
		{
			StopEffect(effectHandle.second[i]);
		}
	}
}

// 全エフェクト再生開始
void ResourceManager::PlayAllEfect()
{
	for (std::pair<std::string, std::vector<int>> effectHandle : mpEffectHandleContainer->GetHandleMap())
	{
		for (int i = 1; i < effectHandle.second.size(); i++)
		{
			PlayEffect(effectHandle.second[i], 1.0f);
		}
	}
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
	mnEffectDrawPreHandle = GetGraphHandle(msResourceFile + "Effect/Background.png");
}

// エフェクト終了
void ResourceManager::EffectFinalize()
{
    for (auto &handle : mpEffectHandleContainer->GetHandleMap())
    {
        DeleteEffekseerEffect(handle.second[0]);
    }

	delete mpEffectHandleContainer;
    // mmEffectHandle.clear();
    // mmEffectHandle.clear();
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