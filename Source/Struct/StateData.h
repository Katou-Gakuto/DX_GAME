#pragma once

// ステート変更条件情報
template<typename stateNumber>
struct STATE_CHANGE_CRIERIA_DATA
{
    stateNumber ChangeNumber;    // 変更ステートナンバー
    bool(*ChangeFlag)();   // 変更フラグ用関数

    STATE_CHANGE_CRIERIA_DATA() = default;

    STATE_CHANGE_CRIERIA_DATA(stateNumber changeNumber, bool (*changeFlag)())
    : ChangeNumber(changeNumber)
    , ChangeFlag(changeFlag)
    {
    }
};