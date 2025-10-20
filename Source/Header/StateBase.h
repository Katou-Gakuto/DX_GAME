#pragma once

// ステートベース
class StateBase
{
protected:
	int mnStateNumber = -1;
public:
	StateBase() = default;
	virtual ~StateBase() = default;

	int GetStateNumber() const { return mnStateNumber; }
};