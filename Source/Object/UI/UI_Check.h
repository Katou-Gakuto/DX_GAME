#pragma once
#include <string>

#include "ObjectBases.h"

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

public:
    UI_Check(void* yesArgument, void* noArgument, void(T::*yesExecuteMemberFunction)(void*), void(T::*noExecuteMemberFunction)(void*), T* yesFunctionPointer, T* noFunctionPointer, std::string messageWord, std::string yesWord = "YES", std::string noWord = "NO");
    ~UI_Check();

private:
    /*UI初期化*/
    void UIInitilize() override;
    /*UI初期化*/
    void UILastInitilize() override;
    /*UI終了*/
    void UIFinalize() override;
    /*UI更新*/
    void UIUpdate() override;
    /*UI最終更新*/
    void UILastUpdate() override;
    /*UI描画*/
    void UIDraw() override;

    /*選択決定時処理*/
    void DecisionProcess() override;
};