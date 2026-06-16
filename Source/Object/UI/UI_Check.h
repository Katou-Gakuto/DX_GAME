#pragma once
#include <string>

#include "ResourceData.h"
#include "TimeData.h"

#include "DxLib.h"

#include "ObjectBase.h"
#include "ResourceManager.h"
#include "UI_Check.h"

#include "Master.h"
#include"ImguiManager.h"

const int TEST_NUMBER = 15;
static VECTOR mvDrawTestPossCheck[TEST_NUMBER] = {};

template<typename T>
class UI_Check : public UIBase
{
private:
    // yes時の実行関数に渡す引数
    void* mpYesArgument;
    // no時の実行関数に渡す引数
    void* mpNoArgument;

    // yes実行関数
    void (T::*mfnYesExecuteMemberFunction)(void*);
    // yes実行関数の呼び元のポインタ
    T* mpYesFunctionPointer;
    // no実行関数
    void (T::*mfnNoExecuteMemberFunction)(void*);
    // no実行関数の呼び元のポインタ
    T* mpNoFunctionPointer;

    // メッセージ
    std::string msMessageWord;
    // yesの言葉
    std::string msYesWord;
    // noの言葉
    std::string msNoWord;
    
	int mnCheckHandle;	// チェック文字ハンドル
	int mnSelectHandle;	// 選択文字ハンドル

    FRAME_DATA mstStartframe;   // 開始フレーム

public:
    UI_Check(void* yesArgument, void* noArgument, void(T::*yesExecuteMemberFunction)(void*), void(T::*noExecuteMemberFunction)(void*), T* yesFunctionPointer, T* noFunctionPointer, std::string messageWord, std::string yesWord = "YES", std::string noWord = "NO")
    : UIBase(true, 2, true, true)
    , mpYesArgument(yesArgument)
    , mpNoArgument(noArgument)
    , mfnYesExecuteMemberFunction(yesExecuteMemberFunction)
    , mfnNoExecuteMemberFunction(noExecuteMemberFunction)
    , mpYesFunctionPointer(yesFunctionPointer)
    , mpNoFunctionPointer(noFunctionPointer)
    , msMessageWord(messageWord)
    , msYesWord(yesWord)
    , msNoWord(noWord)
    , mstStartframe(Master::mpTimeManager->GetFrame() + 1/*1フレーム分ずらす*/)
    {
        printfDx("確認\n");
    }
    ~UI_Check(){}

private:
    /*UI初期化*/
    void UIInitilize() override
    {
        { // 文字サイズハンドル設定
            mnCheckHandle = CreateFontToHandle(NULL, 40, 5);
            mnSelectHandle = CreateFontToHandle(NULL, 30, 5);
        }
        mnSelectNumber = 1;

        for (int i = 0; i < TEST_NUMBER; i++)
        {
            IMGUI_FLOAT_DATA imguiFloatData;
            imguiFloatData.AddVariable(&mvDrawTestPossCheck[i].x);
            imguiFloatData.AddVariable(&mvDrawTestPossCheck[i].y);
            imguiFloatData.SetLabel("UICheck_Pos_");
            imguiFloatData.SetImguiType(IMGUI_TYPE::DRAG2);
            imguiFloatData.SetMin(-10.0f);
            imguiFloatData.SetMax(10.0f);
            imguiFloatData.SetStep(0.1f);
            imguiFloatData.SetSpeed(0.01f);
            imguiFloatData.SetStepFast(0.1f);

            Master::mpImguiManager->SetFloatImgui(imguiFloatData);
        }
        mvDrawTestPossCheck[13] = VGet(0.28f, 0.38f, 0.0f);
        mvDrawTestPossCheck[14] = VGet(0.62f, 0.72f, 0.0f);
        mvDrawTestPossCheck[0] = VGet(0.29f, 0.39f, 0.0f);
        mvDrawTestPossCheck[1] = VGet(0.61f, 0.71f, 0.0f);
        mvDrawTestPossCheck[2] = VGet(0.295f, 0.54f, 0.0f);
        mvDrawTestPossCheck[3] = VGet(0.415f, 0.64f, 0.0f);
        mvDrawTestPossCheck[4] = VGet(0.305f, 0.55f, 0.0f);
        mvDrawTestPossCheck[5] = VGet(0.405f, 0.63f, 0.0f);
        mvDrawTestPossCheck[6] = VGet(0.485f, 0.54f, 0.0f);
        mvDrawTestPossCheck[7] = VGet(0.605f, 0.64f, 0.0f);
        mvDrawTestPossCheck[8] = VGet(0.495f, 0.55f, 0.0f);
        mvDrawTestPossCheck[9] = VGet(0.595f, 0.63f, 0.0f);
        mvDrawTestPossCheck[10] = VGet(0.31f, 0.45f, 0.0f);
        mvDrawTestPossCheck[11] = VGet(0.32f, 0.56f, 0.0f);
        mvDrawTestPossCheck[12] = VGet(0.5225f, 0.56f, 0.0f);
    }
    /*UI初期化*/
    void UISceneLastInitilize() override{}
    /*UI終了*/
    void UIFinalize() override
    {
        DeleteFontToHandle(mnCheckHandle);
        DeleteFontToHandle(mnSelectHandle);
    }
    /*UI更新*/
    void UIUpdate() override
    {
        LeftRightSelectProcess();
        if (mstStartframe <= Master::mpTimeManager->GetFrame())
        {
            DefaultDecision();
        }
        DefaultCloce();
        printfDx("%d 確認\n", mnSelectNumber);
    }
    /*UI最終更新*/
    void UILastUpdate() override{}
    /*UI描画*/
    void UIDraw() override
    {
        DisplaySize displaySize = ResourceManager::mstDisplaySize;

        DrawBoxAA(displaySize.Left_RatioWidth(mvDrawTestPossCheck[13].x), displaySize.Up_RatioHeight(mvDrawTestPossCheck[13].y),
                displaySize.Left_RatioWidth(mvDrawTestPossCheck[14].x), displaySize.Up_RatioHeight(mvDrawTestPossCheck[14].y), GetColor(200, 200, 200), TRUE);

        DrawBoxAA(displaySize.Left_RatioWidth(mvDrawTestPossCheck[0].x), displaySize.Up_RatioHeight(mvDrawTestPossCheck[0].y),
                displaySize.Left_RatioWidth(mvDrawTestPossCheck[1].x), displaySize.Up_RatioHeight(mvDrawTestPossCheck[1].y), GetColor(100, 100, 100), TRUE);

        // YES
        DrawBoxAA(displaySize.Left_RatioWidth(mvDrawTestPossCheck[2].x), displaySize.Up_RatioHeight(mvDrawTestPossCheck[2].y), displaySize.Left_RatioWidth(mvDrawTestPossCheck[3].x), displaySize.Up_RatioHeight(mvDrawTestPossCheck[3].y), GetColor(0, 0, 0), TRUE);
        DrawBoxAA(displaySize.Left_RatioWidth(mvDrawTestPossCheck[4].x), displaySize.Up_RatioHeight(mvDrawTestPossCheck[4].y), displaySize.Left_RatioWidth(mvDrawTestPossCheck[5].x), displaySize.Up_RatioHeight(mvDrawTestPossCheck[5].y), ((mnSelectNumber == 1) ? GetColor(200, 200, 200) : GetColor(255, 255, 255)), TRUE);

        // NO
        DrawBoxAA(displaySize.Left_RatioWidth(mvDrawTestPossCheck[6].x), displaySize.Up_RatioHeight(mvDrawTestPossCheck[6].y), displaySize.Left_RatioWidth(mvDrawTestPossCheck[7].x), displaySize.Up_RatioHeight(mvDrawTestPossCheck[7].y), GetColor(0, 0, 0), TRUE);
        DrawBoxAA(displaySize.Left_RatioWidth(mvDrawTestPossCheck[8].x), displaySize.Up_RatioHeight(mvDrawTestPossCheck[8].y), displaySize.Left_RatioWidth(mvDrawTestPossCheck[9].x), displaySize.Up_RatioHeight(mvDrawTestPossCheck[9].y), ((mnSelectNumber == 0) ? GetColor(200, 200, 200) : GetColor(255, 255, 255)), TRUE);

        // Check文字
        DrawStringToHandle(displaySize.Left_RatioWidth(mvDrawTestPossCheck[10].x), displaySize.Up_RatioHeight(mvDrawTestPossCheck[10].y), msMessageWord.c_str(), GetColor(0, 0, 0), mnCheckHandle);

        // 選択文字
        DrawStringToHandle(displaySize.Left_RatioWidth(mvDrawTestPossCheck[11].x), displaySize.Up_RatioHeight(mvDrawTestPossCheck[11].y), msYesWord.c_str(), GetColor(0, 0, 0), mnSelectHandle);
        DrawStringToHandle(displaySize.Left_RatioWidth(mvDrawTestPossCheck[12].x), displaySize.Up_RatioHeight(mvDrawTestPossCheck[12].y), msNoWord.c_str(), GetColor(0, 0, 0), mnSelectHandle);
    }

    /*選択決定時処理*/
    void DecisionProcess() override
    {
        switch (mnSelectNumber)
        {
        case 0:
            (mpYesFunctionPointer->*mfnYesExecuteMemberFunction)(mpYesArgument);
            break;

        case 1:
            (mpNoFunctionPointer->*mfnNoExecuteMemberFunction)(mpNoArgument);
            break;
        }

        CloceProcess();
    }

    /*削除*/
    void CloceProcess() override
    {
        (mpNoFunctionPointer->*mfnNoExecuteMemberFunction)(mpNoArgument);
        SetDeleteFlag(true);
    }
};