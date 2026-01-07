
#include "FSM.h"
#include "ModelBase.h"
#include "ModelsControllerBase.h"

ModelsControllerBase::ModelsControllerBase()
{
    mpFsm = nullptr;

    mpModelList.clear();
}

ModelsControllerBase::~ModelsControllerBase()
{
    delete mpFsm;
}

// ‰Šú‰»
void ModelsControllerBase::Initilize()
{
    mpModelList[0]->Initilize();
}

// ƒ‚ƒfƒ‹’Ç‰Á
void ModelsControllerBase::AddModel(ModelBase* model)
{
    mpModelList.push_back(model);
}