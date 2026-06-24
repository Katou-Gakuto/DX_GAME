#pragma once
#include <vector>

#include "StateBase.h"
#include "StateEnum.h"
#include "StateCharacterBase.h"

/*==============================*/
/*        移動ステート群        */
/*==============================*/

/* 前方移動 */
class StateMoveFront : public IStateCharacter
{
public:
    StateMoveFront(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias, STATE_TYPE_CHARACTER stateNumber);

    void Initilize(CharacterBase* character) override;
    void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
    void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState) override;

    void Update(CharacterBase* character) override;
    void LastUpdate(CharacterBase* character) override;
    void Draw(CharacterBase* character) override;
};

/* 後方移動 */
class StateMoveBack : public IStateCharacter
{
public:
    StateMoveBack(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias, STATE_TYPE_CHARACTER stateNumber);

    void Initilize(CharacterBase* character) override;
    void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
    void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState) override;

    void Update(CharacterBase* character) override;
    void LastUpdate(CharacterBase* character) override;
    void Draw(CharacterBase* character) override;
};

/* 右移動 */
class StateMoveRight : public IStateCharacter
{
public:
    StateMoveRight(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias, STATE_TYPE_CHARACTER stateNumber);

    void Initilize(CharacterBase* character) override;
    void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
    void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState) override;

    void Update(CharacterBase* character) override;
    void LastUpdate(CharacterBase* character) override;
    void Draw(CharacterBase* character) override;
};

/* 左移動 */
class StateMoveLeft : public IStateCharacter
{
public:
    StateMoveLeft(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias, STATE_TYPE_CHARACTER stateNumber);

    void Initilize(CharacterBase* character) override;
    void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
    void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState) override;

    void Update(CharacterBase* character) override;
    void LastUpdate(CharacterBase* character) override;
    void Draw(CharacterBase* character) override;
};

/*==============================*/
/*        斜め移動ステート      */
/*==============================*/

/* 前左 */
class StateMoveFrontLeft : public IStateCharacter
{
public:
    StateMoveFrontLeft(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias, STATE_TYPE_CHARACTER stateNumber);

    void Initilize(CharacterBase* character) override;
    void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
    void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState) override;

    void Update(CharacterBase* character) override;
    void LastUpdate(CharacterBase* character) override;
    void Draw(CharacterBase* character) override;
};

/* 前右 */
class StateMoveFrontRight : public IStateCharacter
{
public:
    StateMoveFrontRight(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias, STATE_TYPE_CHARACTER stateNumber);

    void Initilize(CharacterBase* character) override;
    void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
    void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState) override;

    void Update(CharacterBase* character) override;
    void LastUpdate(CharacterBase* character) override;
    void Draw(CharacterBase* character) override;
};

/* 後左 */
class StateMoveBackLeft : public IStateCharacter
{
public:
    StateMoveBackLeft(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias, STATE_TYPE_CHARACTER stateNumber);

    void Initilize(CharacterBase* character) override;
    void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
    void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState) override;

    void Update(CharacterBase* character) override;
    void LastUpdate(CharacterBase* character) override;
    void Draw(CharacterBase* character) override;
};

/* 後右 */
class StateMoveBackRight : public IStateCharacter
{
public:
    StateMoveBackRight(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias, STATE_TYPE_CHARACTER stateNumber);

    void Initilize(CharacterBase* character) override;
    void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
    void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState) override;

    void Update(CharacterBase* character) override;
    void LastUpdate(CharacterBase* character) override;
    void Draw(CharacterBase* character) override;
};

/*==============================*/
/*        ジャンプステート      */
/*==============================*/

class StateJump : public IStateCharacter
{
public:
    StateJump(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias, STATE_TYPE_CHARACTER stateNumber);

    void Initilize(CharacterBase* character) override;
    void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
    void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState) override;

    void Update(CharacterBase* character) override;
    void LastUpdate(CharacterBase* character) override;
    void Draw(CharacterBase* character) override;
};