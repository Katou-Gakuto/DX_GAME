#pragma once
#include <string>

#include "ResourceData.h"
#include "UtilCalc.h"

class Resource3DModel;
class ResourceGraph;
class ResourceMovie;
class ResourceSound;
class ResourceEffect;

class ResourceManager
{
	/*--------*/
	/*Åyã§í Åz*/
	/*--------*/

public:
	static std::string msResourceFile;
	static DisplaySize mstDisplaySize;

public:
	ResourceManager();
	~ResourceManager();

	void Initilize();
	void Finalize();
	void Update();

	void StartDraw();
	void MiddleDraw();
	void LastDraw();
	void DrawDataRelease();

	/*----------*/
	/*Åyï`âÊÅz*/
	/*----------*/
private:
	int mnShadowMapHandle;
	bool mbDrawShadowMapFlag;

	Resource3DModel* mp3DModel;
	ResourceGraph* mpGraph;
	ResourceMovie* mpMovie;
	ResourceSound* mpSound;
	ResourceEffect* mpEffect;

	void ShadowMapInit();

public:
	void DrawModelHandle(int modelHandle);
	void DrawIndexed(const VERTEX3D* VertexArray, int VertexNum, const unsigned short* IndexArray, int PolygonNum, int GrHandle, int TransFlag);
	void DrawData_Graph(DRAW_GRAPH_DATA drawData);

	/*----------*/
	/*ÅyéÊìæÅz*/
	/*----------*/
public:
	DRAW_GRAPH_DATA GetDrawGraphData(int handle, int x, int y);
	DRAW_GRAPH_DATA GetDrawGraphData(int handle, int x, int y, int sizeX, int sizeY);
	DRAW_GRAPH_DATA GetDrawGraphData(int handle, int x, int y, float sizeXRatio, float sizeYRatio);
	DRAW_GRAPH_DATA GetDrawGraphData(int handle, float xRatio, float yRatio);
	DRAW_GRAPH_DATA GetDrawGraphData(int handle, float xRatio, float yRatio, int sizeX, int sizeY);
	DRAW_GRAPH_DATA GetDrawGraphData(int handle, float xRatio, float yRatio, float sizeXRatio, float sizeYRatio);
	DRAW_GRAPH_DATA GetDrawGraphData(int handle, Vector2_Int pos);
	DRAW_GRAPH_DATA GetDrawGraphData(int handle, Vector2_Int pos, Vector2_Int size);
	DRAW_GRAPH_DATA GetDrawGraphData(int handle, Vector2_Int leftUp, Vector2_Int rightUp, Vector2_Int leftDown, Vector2_Int rightDown);

	inline bool GetShadowMapDrawFlag() const { return mbDrawShadowMapFlag; }

	/*------------*/
	/*Åy3DÉÇÉfÉãÅz*/
	/*------------*/
public:
	int GetModelHandle(std::string fileName);
	void ReduceModelHandle(int handle);

	/*--------*/
	/*ÅyâÊëúÅz*/
	/*--------*/
public:
	int GetGraphHandle(std::string fileName);
	void ReduceGraphHandle(int handle);
	void GetDivGraphHandle(std::string fileName, DIV_GRAPH_DATA* graphData);
	void ReduceDivGraphHandle(int number);

	/*--------*/
	/*ÅyìÆâÊÅz*/
	/*--------*/
public:
	int GetMovieHandle(std::string fileName);
	void ReduceMovie(int handle);
	void PlayMovie(int handle);
	void StopMovie(int handle);
	void MovieReset(int handle);
	void MovieLoop(int handle);

	/*------------*/
	/*ÅyÉTÉEÉìÉhÅz*/
	/*------------*/
public:
	int GetSoundHandle(std::string fileName);
	void ReduceSoundHandle(int handle);
	int Get3DSoundHandle(std::string fileName);
	void Reduce3DSoundHandle(int handle);
	void SetBackSoundHandle(int handle);
	void SoundUpdate();
	void SetPlaySound(int handle, int volume = -1);
	void SetPlay3DSound(int handle, VECTOR position, int volume = -1);
	void Set3DListenerPosition(VECTOR position, VECTOR frontPosition);

	/*----------*/
	/*ÅyÉGÉtÉFÉNÉgÅz*/
	/*----------*/
public:
	int GetEffectResource(std::string fileName, float size = 1.0f);
	int GetEffectHandle(int handle, int oldHandle);
	void DeletePlayEffectHandle(int handle);
	void ReduceEffectDataHandle(int handle);
	void DrawEffect(int handle, VECTOR position, VECTOR angle = UtilCalc::VZero, VECTOR size = UtilCalc::VOne);
	void StopEffect(int handle);
	void PlayEffect(int handle, float speed);
	void StopAllEfect();
	void PlayAllEfect();
};
