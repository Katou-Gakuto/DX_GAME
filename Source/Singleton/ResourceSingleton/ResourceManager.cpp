#include "ResourceManager.h"

#include "Master.h"
#include "DataManager.h"

#include "Resource3DModel.h"
#include "ResourceGraph.h"
#include "ResourceMovie.h"
#include "ResourceSound.h"
#include "ResourceEffect.h"

std::string ResourceManager::msResourceFile = "Resource/";
DisplaySize ResourceManager::mstDisplaySize = DisplaySize();

ResourceManager::ResourceManager()
: mnShadowMapHandle(-1)
, mbDrawShadowMapFlag(false)
, mp3DModel(nullptr)
, mpGraph(nullptr)
, mpMovie(nullptr)
, mpSound(nullptr)
, mpEffect(nullptr)
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::Initilize()
{
	mp3DModel = new Resource3DModel();
	mp3DModel->Initilize();

	mpGraph = new ResourceGraph();
	mpGraph->Initilize();

	mpMovie = new ResourceMovie();
	mpMovie->Initilize();

	mpSound = new ResourceSound();
	mpSound->Initilize(Master::mpDataManager);

	mpEffect = new ResourceEffect();
	mpEffect->Initilize(mpGraph, msResourceFile);

	Vector2_Int setDisplaySize;
	GetScreenState(&setDisplaySize.x, &setDisplaySize.y, &mstDisplaySize.colorBit);
	mstDisplaySize = setDisplaySize;

	SetGlobalAmbientLight(GetColorF(0.3f, 0.3f, 0.3f, 1.0f));

	ShadowMapInit();
}

void ResourceManager::Finalize()
{
	DeleteShadowMap(mnShadowMapHandle);

	if (mp3DModel != nullptr)
	{
		mp3DModel->Finalize();
		delete mp3DModel;
		mp3DModel = nullptr;
	}

	if (mpGraph != nullptr)
	{
		mpGraph->Finalize();
		delete mpGraph;
		mpGraph = nullptr;
	}

	if (mpMovie != nullptr)
	{
		mpMovie->Finalize();
		delete mpMovie;
		mpMovie = nullptr;
	}

	if (mpSound != nullptr)
	{
		mpSound->Finalize();
		delete mpSound;
		mpSound = nullptr;
	}

	if (mpEffect != nullptr)
	{
		mpEffect->Finalize();
		delete mpEffect;
		mpEffect = nullptr;
	}
}

void ResourceManager::Update()
{
	mpSound->SoundUpdate();
}

void ResourceManager::StartDraw()
{
	ShadowMap_DrawSetup(mnShadowMapHandle);
	mbDrawShadowMapFlag = true;
}

void ResourceManager::MiddleDraw()
{
	ShadowMap_DrawEnd();
	mbDrawShadowMapFlag = false;
	SetUseShadowMap(0, mnShadowMapHandle);
}

void ResourceManager::LastDraw()
{
	mpEffect->EffectDrawProcess();
}

void ResourceManager::DrawDataRelease()
{
	SetUseShadowMap(0, -1);
	mpEffect->DrawDataRelease();
}

void ResourceManager::DrawModelHandle(int modelHandle)
{
	mp3DModel->DrawModelHandle(modelHandle);
}

void ResourceManager::DrawIndexed(const VERTEX3D* VertexArray, int VertexNum, const unsigned short* IndexArray, int PolygonNum, int GrHandle, int TransFlag)
{
	DrawPolygonIndexed3D(VertexArray, VertexNum, IndexArray, PolygonNum, GrHandle, TransFlag);
}

void ResourceManager::DrawData_Graph(DRAW_GRAPH_DATA drawData)
{
	mpGraph->DrawData_Graph(drawData);
}

void ResourceManager::ShadowMapInit()
{
	mnShadowMapHandle = MakeShadowMap(4096, 4096);
	SetShadowMapLightDirection(mnShadowMapHandle, VGet(0.5f, -0.5f, 0.5f));
	SetShadowMapDrawArea(mnShadowMapHandle, VGet(-400.0f, -1.0f, -400.0f), VGet(10000.0f, 10000.0f, 10000.0f));
}

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

int ResourceManager::GetModelHandle(std::string fileName)
{
	return mp3DModel->GetModelHandle(fileName);
}

void ResourceManager::ReduceModelHandle(int handle)
{
	mp3DModel->ReduceModelHandle(handle);
}

int ResourceManager::GetGraphHandle(std::string fileName)
{
	return mpGraph->GetGraphHandle(fileName);
}

void ResourceManager::ReduceGraphHandle(int handle)
{
	mpGraph->ReduceGraphHandle(handle);
}

void ResourceManager::GetDivGraphHandle(std::string fileName, DIV_GRAPH_DATA* graphData)
{
	mpGraph->GetDivGraphHandle(fileName, graphData);
}

void ResourceManager::ReduceDivGraphHandle(int number)
{
	mpGraph->ReduceDivGraphHandle(number);
}

int ResourceManager::GetMovieHandle(std::string fileName)
{
	return mpMovie->GetMovieHandle(fileName);
}

void ResourceManager::ReduceMovie(int handle)
{
	mpMovie->ReduceMovie(handle);
}

void ResourceManager::PlayMovie(int handle)
{
	mpMovie->PlayMovie(handle);
}

void ResourceManager::StopMovie(int handle)
{
	mpMovie->StopMovie(handle);
}

void ResourceManager::MovieReset(int handle)
{
	mpMovie->MovieReset(handle);
}

void ResourceManager::MovieLoop(int handle)
{
	mpMovie->MovieLoop(handle);
}

int ResourceManager::GetSoundHandle(std::string fileName)
{
	return mpSound->GetSoundHandle(fileName);
}

void ResourceManager::ReduceSoundHandle(int handle)
{
	mpSound->ReduceSoundHandle(handle);
}

int ResourceManager::Get3DSoundHandle(std::string fileName)
{
	return mpSound->Get3DSoundHandle(fileName);
}

void ResourceManager::Reduce3DSoundHandle(int handle)
{
	mpSound->Reduce3DSoundHandle(handle);
}

void ResourceManager::SetBackSoundHandle(int handle)
{
	mpSound->SetBackSoundHandle(handle);
}

void ResourceManager::SoundUpdate()
{
	mpSound->SoundUpdate();
}

void ResourceManager::SetPlaySound(int handle, int volume)
{
	mpSound->SetPlaySound(handle, volume);
}

void ResourceManager::SetPlay3DSound(int handle, VECTOR position, int volume)
{
	mpSound->SetPlay3DSound(handle, position, volume);
}

void ResourceManager::Set3DListenerPosition(VECTOR position, VECTOR frontPosition)
{
	mpSound->Set3DListenerPosition(position, frontPosition);
}

int ResourceManager::GetEffectResource(std::string fileName, float size)
{
	return mpEffect->GetEffectResource(fileName, size);
}

int ResourceManager::GetEffectHandle(int handle, int oldHandle)
{
	return mpEffect->GetEffectHandle(handle, oldHandle);
}

void ResourceManager::DeletePlayEffectHandle(int handle)
{
	mpEffect->DeletePlayEffectHandle(handle);
}

void ResourceManager::ReduceEffectDataHandle(int handle)
{
	mpEffect->ReduceEffectDataHandle(handle);
}

void ResourceManager::DrawEffect(int handle, VECTOR position, VECTOR angle, VECTOR size)
{
	mpEffect->DrawEffect(handle, position, angle, size);
}

void ResourceManager::StopEffect(int handle)
{
	mpEffect->StopEffect(handle);
}

void ResourceManager::PlayEffect(int handle, float speed)
{
	mpEffect->PlayEffect(handle, speed);
}

void ResourceManager::StopAllEfect()
{
	mpEffect->StopAllEfect();
}

void ResourceManager::PlayAllEfect()
{
	mpEffect->PlayAllEfect();
}
