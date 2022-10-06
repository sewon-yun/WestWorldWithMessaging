#ifndef MINERSDAUGHTER_OWNED_STATES_H
#define MINERSDAUGHTER_OWNED_STATES_H
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

class MinersDaughter;



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class DaughtersGlobalState : public State<MinersDaughter>
{
private:

	DaughtersGlobalState() {}

	//copy ctor and assignment should be private
	DaughtersGlobalState(const DaughtersGlobalState&);
	DaughtersGlobalState& operator=(const DaughtersGlobalState&);

public:

	//this is a singleton
	static DaughtersGlobalState* Instance();

	virtual void Enter(MinersDaughter* daughter) {}

	virtual void Execute(MinersDaughter* daughter);

	virtual void Exit(MinersDaughter* daughter) {}

	virtual bool OnMessage(MinersDaughter* daughter, const Telegram& msg);
};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class PlayingDolls : public State<MinersDaughter>
{
private:

	PlayingDolls() {}

	//copy ctor and assignment should be private
	PlayingDolls(const PlayingDolls&);
	PlayingDolls& operator=(const PlayingDolls&);

public:

	//this is a singleton
	static PlayingDolls* Instance();

	virtual void Enter(MinersDaughter* daughter);

	virtual void Execute(MinersDaughter* daughter);

	virtual void Exit(MinersDaughter* daughter);

	virtual bool OnMessage(MinersDaughter* daughter, const Telegram& msg);

};



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class SleepingInRoom : public State<MinersDaughter>
{
private:

	SleepingInRoom() {}

	//copy ctor and assignment should be private
	SleepingInRoom(const SleepingInRoom&);
	SleepingInRoom& operator=(const SleepingInRoom&);

public:

	//this is a singleton
	static SleepingInRoom* Instance();

	virtual void Enter(MinersDaughter* daughter);

	virtual void Execute(MinersDaughter* daughter);

	virtual void Exit(MinersDaughter* daughter);

	virtual bool OnMessage(MinersDaughter* daughter, const Telegram& msg);

};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class EatStewForDaughter : public State<MinersDaughter>
{
private:

	EatStewForDaughter() {}

	//copy ctor and assignment should be private
	EatStewForDaughter(const EatStewForDaughter&);
	EatStewForDaughter& operator=(const EatStewForDaughter&);

public:

	//this is a singleton
	static EatStewForDaughter* Instance();

	virtual void Enter(MinersDaughter* daughter);

	virtual void Execute(MinersDaughter* daughter);

	virtual void Exit(MinersDaughter* daughter);

	virtual bool OnMessage(MinersDaughter* agent, const Telegram& msg);
};


#endif

