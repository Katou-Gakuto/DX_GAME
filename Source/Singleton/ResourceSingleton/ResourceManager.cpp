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
, mp3DModelResource(nullptr)
, mpGraphResource(nullptr)
, mpDivGraphResource(nullptr)
, mpMovieResource(nullptr)
, mpEffectResource(nullptr)
, mpSoundResource(nullptr)
, mpBackSoundResource(nullptr)
, mp3DSoundResource(nullptr)
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::Initilize()
{
	mp3DModelResource = new Resource3DModel();
	mp3DModelResource->Initilize();

	mpGraphResource = new ResourceGraph();
	mpGraphResource->Initilize();
	mpDivGraphResource = new ResourceDivGraph();
	mpDivGraphResource->Initilize();

	mpMovieResource = new ResourceMovie();
	mpMovieResource->Initilize();

	mpSoundResource= new ResourceSound();
	mpSoundResource->Initilize();
	mpBackSoundResource= new ResourceBackSound();
	mpBackSoundResource->Initilize();
	mp3DSoundResource = new Resource3DSound();
	mp3DSoundResource->Initilize();

	mpEffectResource = new ResourceEffect();
	mpEffectResource->Initilize(mpGraphResource, msResourceFile);

	Vector2_Int setDisplaySize;
	GetScreenState(&setDisplaySize.x, &setDisplaySize.y, &mstDisplaySize.colorBit);
	mstDisplaySize = setDisplaySize;

	SetGlobalAmbientLight(GetColorF(0.3f, 0.3f, 0.3f, 1.0f));

	ShadowMapInit();
}

void ResourceManager::Finalize()
{
	DeleteShadowMap(mnShadowMapHandle);

	if (mp3DModelResource != nullptr)
	{
		mp3DModelResource->Finalize();
		delete mp3DModelResource;
		mp3DModelResource = nullptr;
	}

	{
		if (mpGraphResource != nullptr)
		{
			mpGraphResource->Finalize();
			delete mpGraphResource;
			mpGraphResource = nullptr;
		}

		if (mpDivGraphResource != nullptr)
		{
			mpDivGraphResource->Finalize();
			delete mpDivGraphResource;
			mpDivGraphResource = nullptr;
		}
	}

	if (mpMovieResource != nullptr)
	{
		mpMovieResource->Finalize();
		delete mpMovieResource;
		mpMovieResource = nullptr;
	}

			
	{
		if (mpSoundResource != nullptr)
		{
			mpSoundResource->Finalize();
			delete mpSoundResource;
			mpSoundResource = nullptr;
		}

		if (mpBackSoundResource != nullptr)
		{
			mpBackSoundResource->Finalize();
			delete mpBackSoundResource;
			mpBackSoundResource = nullptr;
		}
		if (mp3DSoundResource != nullptr)
		{
			mp3DSoundResource->Finalize();
			delete mp3DSoundResource;
			mp3DSoundResource = nullptr;
		}
	}

	if (mpEffectResource != nullptr)
	{
		mpEffectResource->Finalize();
		delete mpEffectResource;
		mpEffectResource = nullptr;
	}
}

void ResourceManager::Update()
{
	// サウンドボリュームの更新
	{
		mpSoundResource->SoundUpdate();
		mpBackSoundResource->SoundUpdate();
		mp3DSoundResource->SoundUpdate();
	}
}

void ResourceManager::StartDraw()
{
	// シャドウマップへの描画の準備
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
	// エフェクト描画処理
	mpEffectResource->EffectDrawProcess();
}

void ResourceManager::DrawDataRelease()
{
	// 描画に使用するシャドウマップの設定を解除
	SetUseShadowMap(0, -1);
	
	// エフェクト描画フラグ無効化
	mpEffectResource->EffectDrawFlagReset();
}

// void ResourceManager::DrawModelHandle(int modelHandle)
// {
// 	mp3DModelResource->DrawModelHandle(modelHandle);
// }

// void ResourceManager::DrawIndexed(const VERTEX3D* VertexArray, int VertexNum, const unsigned short* IndexArray, int PolygonNum, int GrHandle, int TransFlag)
// {
// 	DrawPolygonIndexed3D(VertexArray, VertexNum, IndexArray, PolygonNum, GrHandle, TransFlag);
// }

// void ResourceManager::DrawData_Graph(DRAW_GRAPH_DATA drawData)
// {
// 	mpGraphResource->DrawData_Graph(drawData);
// }

void ResourceManager::ShadowMapInit()
{
	mnShadowMapHandle = MakeShadowMap(4096, 4096);
	SetShadowMapLightDirection(mnShadowMapHandle, VGet(0.5f, -0.5f, 0.5f));
	SetShadowMapDrawArea(mnShadowMapHandle, VGet(-400.0f, -1.0f, -400.0f), VGet(10000.0f, 10000.0f, 10000.0f));
}

// int ResourceManager::GetModelHandle(std::string fileName)
// {
// 	return mp3DModel->GetModelHandle(fileName);
// }

// void ResourceManager::ReduceModelHandle(int handle)
// {
// 	mp3DModel->ReduceModelHandle(handle);
// }

// int ResourceManager::GetGraphHandle(std::string fileName)
// {
// 	return mpGraph->GetGraphResource()->GetResourceHandle((fileName);
// }

// void ResourceManager::ReduceGraphHandle(int handle)
// {
// 	mpGraph->ReduceGraphHandle(handle);
// }

// void ResourceManager::GetDivGraphHandle(std::string fileName, DIV_GRAPH_DATA* graphData)
// {
// 	mpGraph->GetDivGraphHandle(fileName, graphData);
// }

// void ResourceManager::ReduceDivGraphHandle(int number)
// {
// 	mpGraph->ReduceDivGraphHandle(number);
// }

// int ResourceManager::GetMovieHandle(std::string fileName)
// {
// 	return mpMovie->GetMovieHandle(fileName);
// }

// void ResourceManager::ReduceMovie(int handle)
// {
// 	mpMovie->ReduceMovie(handle);
// }

// void ResourceManager::PlayMovie(int handle)
// {
// 	mpMovie->PlayMovie(handle);
// }

// void ResourceManager::StopMovie(int handle)
// {
// 	mpMovie->StopMovie(handle);
// }

// void ResourceManager::MovieReset(int handle)
// {
// 	mpMovie->MovieReset(handle);
// }

// void ResourceManager::MovieLoop(int handle)
// {
// 	mpMovie->MovieLoop(handle);
// }

// int ResourceManager::GetSoundHandle(std::string fileName)
// {
// 	return mpSound->GetSoundHandle(fileName);
// }

// void ResourceManager::ReduceSoundHandle(int handle)
// {
// 	mpSound->ReduceSoundHandle(handle);
// }

// int ResourceManager::Get3DSoundHandle(std::string fileName)
// {
// 	return mpSound->Get3DSoundHandle(fileName);
// }

// void ResourceManager::Reduce3DSoundHandle(int handle)
// {
// 	mpSound->Reduce3DSoundHandle(handle);
// }

// void ResourceManager::SetBackSoundHandle(int handle)
// {
// 	mpSound->SetBackSoundHandle(handle);
// }

// void ResourceManager::SoundUpdate()
// {
// 	mpSound->SoundUpdate();
// }

// void ResourceManager::SetPlaySound(int handle, int volume)
// {
// 	mpSound->SetPlaySound(handle, volume);
// }

// void ResourceManager::SetPlay3DSound(int handle, VECTOR position, int volume)
// {
// 	mpSound->SetPlay3DSound(handle, position, volume);
// }

// void ResourceManager::Set3DListenerPosition(VECTOR position, VECTOR frontPosition)
// {
// 	mpSound->Set3DListenerPosition(position, frontPosition);
// }

// int ResourceManager::GetEffectResource(std::string fileName, float size)
// {
// 	return mpEffect->GetEffectResource(fileName, size);
// }

// int ResourceManager::GetEffectHandle(int handle, int oldHandle)
// {
// 	return mpEffect->GetEffectHandle(handle, oldHandle);
// }

// void ResourceManager::DeletePlayEffectHandle(int handle)
// {
// 	mpEffect->DeletePlayEffectHandle(handle);
// }

// void ResourceManager::ReduceEffectDataHandle(int handle)
// {
// 	mpEffect->ReduceEffectDataHandle(handle);
// }

// void ResourceManager::DrawEffect(int handle, VECTOR position, VECTOR angle, VECTOR size)
// {
// 	mpEffect->DrawEffect(handle, position, angle, size);
// }

// void ResourceManager::StopEffect(int handle)
// {
// 	mpEffect->StopEffect(handle);
// }

// void ResourceManager::PlayEffect(int handle, float speed)
// {
// 	mpEffect->PlayEffect(handle, speed);
// }

// void ResourceManager::StopAllEfect()
// {
// 	mpEffect->StopAllEfect();
// }

// void ResourceManager::PlayAllEfect()
// {
// 	mpEffect->PlayAllEfect();
// }
