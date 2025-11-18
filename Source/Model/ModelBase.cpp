#include "ModelBase.h"
#include "UtilCalc.h"

ModelBase::ModelBase()
: mvSize(UtilCalc::VZero)
{
}
ModelBase::~ModelBase()
{
}

// èâä˙âª
void ModelBase::Initilize()
{
	ModelInitilize();
}

// èIóπ
void ModelBase::Finalize()
{
	ModelFinalize();
}