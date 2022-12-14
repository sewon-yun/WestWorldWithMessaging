#ifndef MINERSBROTHER_H
#define MINERSBROTHER_H
//------------------------------------------------------------------------
//
//  Name: MinersBrother.h
//
//  Desc: class to implement Miner Bob's son.
//
//  Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include <string>

#include "fsm/State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "MinersBrotherOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "Miner.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"



class MinersBrother : public BaseGameEntity
{
private:

    //an instance of the state machine class
    StateMachine<MinersBrother>* m_pStateMachine;

    location_type   m_Location;

    bool            m_bPlayingSoccer;


public:

    MinersBrother(int id) :m_Location(shack),
        m_bPlayingSoccer(false),
        BaseGameEntity(id)

    {
        //set up the state machine
        m_pStateMachine = new StateMachine<MinersBrother>(this);

        m_pStateMachine->SetCurrentState(DoGame::Instance());

        m_pStateMachine->SetGlobalState(BrothersGlobalState::Instance());
    }

    ~MinersBrother() { delete m_pStateMachine; }


    //this must be implemented
    void          Update();

    //so must this
    virtual bool  HandleMessage(const Telegram& msg);

    StateMachine<MinersBrother>* GetFSM()const { return m_pStateMachine; }

    //----------------------------------------------------accessors
    location_type Location()const { return m_Location; }
    void          ChangeLocation(location_type loc) { m_Location = loc; }

    bool          PlayingSoccer()const { return m_bPlayingSoccer; }
    void          SetPlayingSoccer(bool val) { m_bPlayingSoccer = val; }

};

#endif
