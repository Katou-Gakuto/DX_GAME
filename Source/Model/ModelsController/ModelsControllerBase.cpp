
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
    // ƒ‚ƒfƒ‹‰Šú‰»
    for (int i = 0; i < mpModelList.size(); i++)
    {
        mpModelList[i]->Initilize();
    }

    // FSMİ’è
    mpFsm = new FSMModelsController();
    mpFsm->IncreaseSubStateMapSize(mpModelList.size() - 1);
}

// ƒ‚ƒfƒ‹’Ç‰Á
void ModelsControllerBase::AddModel(ModelBase* model)
{
    mpModelList.push_back(model);
}