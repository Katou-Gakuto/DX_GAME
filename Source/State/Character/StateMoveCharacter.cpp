#include <vector>

#include "ObjectBase_Character.h"
#include "StateBase.h"
#include "StateEnum.h"
#include "StateCharacterBase.h"
#include "StateMoveCharacter.h"

/*==============================*/
/*      前方移動               */
/*==============================*/

StateMoveFront::StateMoveFront(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias, STATE_TYPE_CHARACTER stateNumber)
: IStateCharacter(stateChangeCriterias, stateNumber, STATE_TYPE_CHARACTER::MOVE_FRONT)
{
}

void StateMoveFront::Initilize(CharacterBase* character)
{
}

void StateMoveFront::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
}

void StateMoveFront::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
}

void StateMoveFront::Update(CharacterBase* character)
{
    character->SetFrontMove();
}

void StateMoveFront::LastUpdate(CharacterBase* character)
{
}

void StateMoveFront::Draw(CharacterBase* character)
{
}

/*==============================*/
/*      後方移動               */
/*==============================*/

StateMoveBack::StateMoveBack(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias, STATE_TYPE_CHARACTER stateNumber)
: IStateCharacter(stateChangeCriterias, stateNumber, STATE_TYPE_CHARACTER::MOVE_BACK)
{
}

void StateMoveBack::Initilize(CharacterBase* character)
{
}

void StateMoveBack::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
}

void StateMoveBack::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
}

void StateMoveBack::Update(CharacterBase* character)
{
    character->SetBackMove();
}

void StateMoveBack::LastUpdate(CharacterBase* character)
{
}

void StateMoveBack::Draw(CharacterBase* character)
{
}

/*==============================*/
/*      右移動                 */
/*==============================*/

StateMoveRight::StateMoveRight(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias, STATE_TYPE_CHARACTER stateNumber)
: IStateCharacter(stateChangeCriterias, stateNumber, STATE_TYPE_CHARACTER::MOVE_RIGHT)
{
}

void StateMoveRight::Initilize(CharacterBase* character)
{
}

void StateMoveRight::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
}

void StateMoveRight::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
}

void StateMoveRight::Update(CharacterBase* character)
{
    character->SetRightMove();
}

void StateMoveRight::LastUpdate(CharacterBase* character)
{
}

void StateMoveRight::Draw(CharacterBase* character)
{
}

/*==============================*/
/*      左移動                 */
/*==============================*/

StateMoveLeft::StateMoveLeft(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias, STATE_TYPE_CHARACTER stateNumber)
: IStateCharacter(stateChangeCriterias, stateNumber, STATE_TYPE_CHARACTER::MOVE_LEFT)
{
}

void StateMoveLeft::Initilize(CharacterBase* character)
{
}

void StateMoveLeft::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
}

void StateMoveLeft::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
}

void StateMoveLeft::Update(CharacterBase* character)
{
    character->SetLeftMove();
}

void StateMoveLeft::LastUpdate(CharacterBase* character)
{
}

void StateMoveLeft::Draw(CharacterBase* character)
{
}

/*==============================*/
/*      前左                   */
/*==============================*/

StateMoveFrontLeft::StateMoveFrontLeft(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias, STATE_TYPE_CHARACTER stateNumber)
: IStateCharacter(stateChangeCriterias, stateNumber, STATE_TYPE_CHARACTER::MOVE_FRONT_LEFT)
{
}

void StateMoveFrontLeft::Initilize(CharacterBase* character)
{
}

void StateMoveFrontLeft::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
}

void StateMoveFrontLeft::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
}

void StateMoveFrontLeft::Update(CharacterBase* character)
{
    character->SetFrontMove();
    character->SetLeftMove();
}

void StateMoveFrontLeft::LastUpdate(CharacterBase* character)
{
}

void StateMoveFrontLeft::Draw(CharacterBase* character)
{
}

/*==============================*/
/*      前右                   */
/*==============================*/

StateMoveFrontRight::StateMoveFrontRight(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias, STATE_TYPE_CHARACTER stateNumber)
: IStateCharacter(stateChangeCriterias, stateNumber, STATE_TYPE_CHARACTER::MOVE_FRONT_RIGHT)
{
}

void StateMoveFrontRight::Initilize(CharacterBase* character)
{
}

void StateMoveFrontRight::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
}

void StateMoveFrontRight::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
    character->SetFrontMove();
    character->SetRightMove();
}

void StateMoveFrontRight::Update(CharacterBase* character)
{
}

void StateMoveFrontRight::LastUpdate(CharacterBase* character)
{
}

void StateMoveFrontRight::Draw(CharacterBase* character)
{
}

/*==============================*/
/*      後左                   */
/*==============================*/

StateMoveBackLeft::StateMoveBackLeft(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias, STATE_TYPE_CHARACTER stateNumber)
: IStateCharacter(stateChangeCriterias, stateNumber, STATE_TYPE_CHARACTER::MOVE_BACK_LEFT)
{
}

void StateMoveBackLeft::Initilize(CharacterBase* character)
{
}

void StateMoveBackLeft::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
}

void StateMoveBackLeft::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
}

void StateMoveBackLeft::Update(CharacterBase* character)
{
    character->SetBackMove();
    character->SetLeftMove();
}

void StateMoveBackLeft::LastUpdate(CharacterBase* character)
{
}

void StateMoveBackLeft::Draw(CharacterBase* character)
{
}

/*==============================*/
/*      後右                   */
/*==============================*/

StateMoveBackRight::StateMoveBackRight(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias, STATE_TYPE_CHARACTER stateNumber)
: IStateCharacter(stateChangeCriterias, stateNumber, STATE_TYPE_CHARACTER::MOVE_BACK_RIGHT)
{
}

void StateMoveBackRight::Initilize(CharacterBase* character)
{
}

void StateMoveBackRight::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
}

void StateMoveBackRight::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
}

void StateMoveBackRight::Update(CharacterBase* character)
{
    character->SetBackMove();
    character->SetRightMove();
}

void StateMoveBackRight::LastUpdate(CharacterBase* character)
{
}

void StateMoveBackRight::Draw(CharacterBase* character)
{
}

/*==============================*/
/*      ジャンプ               */
/*==============================*/

StateJump::StateJump(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias, STATE_TYPE_CHARACTER stateNumber)
: IStateCharacter(stateChangeCriterias, stateNumber, STATE_TYPE_CHARACTER::JUMP)
{
}

void StateJump::Initilize(CharacterBase* character)
{
}

void StateJump::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
    character->SetJump();
}

void StateJump::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
}

void StateJump::Update(CharacterBase* character)
{
}

void StateJump::LastUpdate(CharacterBase* character)
{
}

void StateJump::Draw(CharacterBase* character)
{
}