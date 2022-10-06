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
class DoHomeWork : public State<MinersSon>
{
private:

	DoHomeWork() {}

	//copy ctor and assignment should be private
	DoHomeWork(const DoHomeWork&);
	DoHomeWork& operator=(const DoHomeWork&);

public:

	//this is a singleton
	static DoHomeWork* Instance();

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
class PlaySoccer : public State<MinersSon>
{
private:

	PlaySoccer() {}

	//copy ctor and assignment should be private
	PlaySoccer(const PlaySoccer&);
	PlaySoccer& operator=(const PlaySoccer&);

public:

	//this is a singleton
	static PlaySoccer* Instance();

	virtual void Enter(MinersSon* son);

	virtual void Execute(MinersSon* son);

	virtual void Exit(MinersSon* son);

	virtual bool OnMessage(MinersSon* son, const Telegram& msg);
};

class EatStewForSon : public State<MinersSon>
{
private:

	EatStewForSon() {}

	//copy ctor and assignment should be private
	EatStewForSon(const EatStewForSon&);
	EatStewForSon& operator=(const EatStewForSon&);

public:

	//this is a singleton
	static EatStewForSon* Instance();

	virtual void Enter(MinersSon* son);

	virtual void Execute(MinersSon* son);

	virtual void Exit(MinersSon* son);

	virtual bool OnMessage(MinersSon* agent, const Telegram& msg);
};


#endif

