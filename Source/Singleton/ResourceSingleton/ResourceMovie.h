#pragma once
#include <string>

#include "HandleContainer.h"

class ResourceMovie
{
private:
	HandleContainer<std::string>* mpMovieHandleContainer;

public:
	ResourceMovie();
	~ResourceMovie();

	void Initilize();
	void Finalize();

	int GetMovieHandle(std::string fileName);
	void ReduceMovie(int handle);

	void PlayMovie(int handle);
	void StopMovie(int handle);
	void MovieReset(int handle);
	void MovieLoop(int handle);
};
