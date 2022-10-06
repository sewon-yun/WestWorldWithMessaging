#ifndef MINERSSON_OWNED_STATES_H
#define MINERSSON_OWNED_STATES_H
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

class MinersSon;



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class SonsGlobalState : public State<MinersSon>
{
private:

	SonsGlobalState() {}

	//copy ctor and assignment should be private
	SonsGlobalState(const SonsGlobalState&);
	SonsGlobalState& operator=(const SonsGlobalState&);

public:

	//this is a singleton
	static SonsGlobalState* Instance();

	virtual void Enter(MinersSon* son) {}

	virtual void Execute(MinersSon* son);

	virtual void Exit(MinersSon* son) {}

	virtual bool OnMessage(MinersSon* son, const Telegram& msg);
};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class DoHouseWork1 : public State<MinersSon>
{
private:

	DoHouseWork1() {}

	//copy ctor and assignment should be private
	DoHouseWork1(const DoHouseWork1&);
	DoHouseWork1& operator=(const DoHouseWork1&);

public:

	//this is a singleton
	static DoHouseWork1* Instance();

	virtual void Enter(MinersSon* son);

	virtual void Execute(MinersSon* son);

	virtual void Exit(MinersSon* son);

	virtual bool OnMessage(MinersSon* son, const Telegram& msg);

};



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class VisitBathroom1 : public State<MinersSon>
{
private:

	VisitBathroom1() {}

	//copy ctor and assignment should be private
	VisitBathroom1(const VisitBathroom1&);
	VisitBathroom1& operator=(const VisitBathroom1&);

public:

	//this is a singleton
	static VisitBathroom1* Instance();

	virtual void Enter(MinersSon* son);

	virtual void Execute(MinersSon* son);

	virtual void Exit(MinersSon* son);

	virtual bool OnMessage(MinersSon* son, const Telegram& msg);

};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class CookStew1 : public State<MinersSon>
{
private:

	CookStew1() {}

	//copy ctor and assignment should be private
	CookStew1(const CookStew1&);
	CookStew1& operator=(const CookStew1&);

public:

	//this is a singleton
	static CookStew1* Instance();

	virtual void Enter(MinersSon* son);

	virtual void Execute(MinersSon* son);

	virtual void Exit(MinersSon* son);

	virtual bool OnMessage(MinersSon* son, const Telegram& msg);
};


#endif