#ifndef MINERSBROTHER_OWNED_STATES_H
#define MINERSBROTHER_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   MinersSonOwnedStates.h
//
//  Desc:   All the states that can be assigned to the MinersSon class
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "fsm/State.h"

class MinersBrother;



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class BrothersGlobalState : public State<MinersBrother>
{
private:

	BrothersGlobalState() {}

	//copy ctor and assignment should be private
	BrothersGlobalState(const BrothersGlobalState&);
	BrothersGlobalState& operator=(const BrothersGlobalState&);

public:

	//this is a singleton
	static BrothersGlobalState* Instance();

	virtual void Enter(MinersBrother* brother) {}

	virtual void Execute(MinersBrother* brother);

	virtual void Exit(MinersBrother* brother) {}

	virtual bool OnMessage(MinersBrother* brother, const Telegram& msg);
};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class DoGame : public State<MinersBrother>
{
private:

	DoGame() {}

	//copy ctor and assignment should be private
	DoGame(const DoGame&);
	DoGame& operator=(const DoGame&);

public:

	//this is a singleton
	static DoGame* Instance();

	virtual void Enter(MinersBrother* brother);

	virtual void Execute(MinersBrother* brother);

	virtual void Exit(MinersBrother* brother);

	virtual bool OnMessage(MinersBrother* brother, const Telegram& msg);

};



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class WorkHard : public State<MinersBrother>
{
private:

	WorkHard() {}

	//copy ctor and assignment should be private
	WorkHard(const WorkHard&);
	WorkHard& operator=(const WorkHard&);

public:

	//this is a singleton
	static WorkHard* Instance();

	virtual void Enter(MinersBrother* brother);

	virtual void Execute(MinersBrother* brother);

	virtual void Exit(MinersBrother* brother);

	virtual bool OnMessage(MinersBrother* brother, const Telegram& msg);

};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class PlaySoccerWithNephew : public State<MinersBrother>
{
private:

	PlaySoccerWithNephew() {}

	//copy ctor and assignment should be private
	PlaySoccerWithNephew(const PlaySoccerWithNephew&);
	PlaySoccerWithNephew& operator=(const PlaySoccerWithNephew&);

public:

	//this is a singleton
	static PlaySoccerWithNephew* Instance();

	virtual void Enter(MinersBrother* brother);

	virtual void Execute(MinersBrother* brother);

	virtual void Exit(MinersBrother* brother);

	virtual bool OnMessage(MinersBrother* brother, const Telegram& msg);
};

class EatStewForBrother : public State<MinersBrother>
{
private:

	EatStewForBrother() {}

	//copy ctor and assignment should be private
	EatStewForBrother(const EatStewForBrother&);
	EatStewForBrother& operator=(const EatStewForBrother&);

public:

	//this is a singleton
	static EatStewForBrother* Instance();

	virtual void Enter(MinersBrother* brother);

	virtual void Execute(MinersBrother* brother);

	virtual void Exit(MinersBrother* brother);

	virtual bool OnMessage(MinersBrother* agent, const Telegram& msg);
};


#endif

