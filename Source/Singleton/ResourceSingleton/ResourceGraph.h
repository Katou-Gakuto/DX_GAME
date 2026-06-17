#pragma once
#include <map>
#include <string>
#include <vector>

#include "ResourceData.h"
#include "HandleContainer.h"

class ResourceGraph
{
private:
	HandleContainer<std::string>* mpGraphHandleContainer;

	std::map<std::string, DIV_GRAPH_DATA> mmDivGraphHandle;
	std::vector<std::string> msDivGraphFileNames;

public:
	ResourceGraph();
	~ResourceGraph();

	void Initilize();
	void Finalize();

	int GetGraphHandle(std::string fileName);
	void ReduceGraphHandle(int handle);

	void GetDivGraphHandle(std::string fileName, DIV_GRAPH_DATA* graphData);
	void ReduceDivGraphHandle(int number);

	void DrawData_Graph(DRAW_GRAPH_DATA drawData);
};
