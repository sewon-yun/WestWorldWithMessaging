#ifndef MINERSDAUGHTER_H
#define MINERSDAUGHTER_H
//------------------------------------------------------------------------
//
//  Name: MinersSon.h
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
#include "MinersDaughterOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "Miner.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"



class MinersDaughter : public BaseGameEntity
{
private:

    //an instance of the state machine class
    StateMachine<MinersDaughter>* m_pStateMachine;

    location_type   m_Location;


public:

    MinersDaughter(int id) :m_Location(shack),
        BaseGameEntity(id)

    {
        //set up the state machine
        m_pStateMachine = new StateMachine<MinersDaughter>(this);

        m_pStateMachine->SetCurrentState(PlayingDolls::Instance());

        m_pStateMachine->SetGlobalState(DaughtersGlobalState::Instance());
    }

    ~MinersDaughter() { delete m_pStateMachine; }


    //this must be implemented
    void          Update();

    //so must this
    virtual bool  HandleMessage(const Telegram& msg);

    StateMachine<MinersDaughter>* GetFSM()const { return m_pStateMachine; }

    //----------------------------------------------------accessors
    location_type Location()const { return m_Location; }
    void          ChangeLocation(location_type loc) { m_Location = loc; }

};

#endif
