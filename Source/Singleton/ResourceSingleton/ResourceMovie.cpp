#include "ResourceMovie.h"

#include "DxLib.h"

#ifdef _DEBUG
#include "DebugLogs/DebugLog.h"
#endif

ResourceMovie::ResourceMovie()
: mpMovieHandleContainer(nullptr)
{
}

ResourceMovie::~ResourceMovie()
{
}

void ResourceMovie::Initilize()
{
	mpMovieHandleContainer = new HandleContainer<std::string>();
	mpMovieHandleContainer->SetHandleFlag(HANDLE_FLAG::NONE);
}

void ResourceMovie::Finalize()
{
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
	mpMovieHandleContainer = nullptr;
}

int ResourceMovie::GetMovieHandle(std::string fileName)
{
#ifdef _DEBUG
	int handle = mpMovieHandleContainer->RegisterHandle(LoadGraph(fileName.c_str()), fileName);
	DEBUG::SaveText("動画ハンドル取得 : " + fileName + " : " + std::to_string(handle) + '\n');
	return handle;
#endif
	return mpMovieHandleContainer->RegisterHandle(LoadGraph(fileName.c_str()), fileName);
}

void ResourceMovie::ReduceMovie(int handle)
{
	std::vector<int> deleteHandle = mpMovieHandleContainer->DeleteHandle(handle);

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
}

void ResourceMovie::PlayMovie(int handle)
{
	PlayMovieToGraph(handle);
}

void ResourceMovie::StopMovie(int handle)
{
	PauseMovieToGraph(handle);
}

void ResourceMovie::MovieReset(int handle)
{
	SeekMovieToGraph(handle, 0);
}

void ResourceMovie::MovieLoop(int handle)
{
	if (GetMovieStateToGraph(handle) != 1)
	{
		MovieReset(handle);
		PlayMovie(handle);
	}
}
