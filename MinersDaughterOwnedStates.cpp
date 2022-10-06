#include "MinersDaughterOwnedStates.h"
#include "MinerOwnedStates.h"
#include "MinersDaughter.h"
#include "Locations.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//-----------------------------------------------------------------------Global state

DaughtersGlobalState* DaughtersGlobalState::Instance()
{
    static DaughtersGlobalState instance;

    return &instance;
}


void DaughtersGlobalState::Execute(MinersDaughter* daughter)
{
    //1 in 10 chance of needing the bathroom (provided she is not already
    //in the bathroom)
    if ((RandFloat() < 0.1) &&
        !daughter->GetFSM()->isInState(*SleepingInRoom::Instance()))
    {
        daughter->GetFSM()->ChangeState(SleepingInRoom::Instance());
    }
}

bool DaughtersGlobalState::OnMessage(MinersDaughter* daughter, const Telegram& msg)
{
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg)
    {
    case Msg_StewReady:
    {
        cout << "\nMessage handled by " << GetNameOfEntity(daughter->ID()) << " at time: "
            << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        cout << "\n" << GetNameOfEntity(daughter->ID()) <<
            ": I'm busy, eat later!";

        daughter->GetFSM()->ChangeState(EatStewForDaughter::Instance());
        return true;
    }
    }//end switch

    return false;
}

//-------------------------------------------------------------------------DoHouseWork

PlayingDolls* PlayingDolls::Instance()
{
    static PlayingDolls instance;

    return &instance;
}


void PlayingDolls::Enter(MinersDaughter* daughter)
{
    cout << "\n" << GetNameOfEntity(daughter->ID()) << ": Where's my Bobby!!";
}


void PlayingDolls::Execute(MinersDaughter* daughter)
{
    switch (RandInt(0, 1))
    {
    case 0:

        cout << "\n" << GetNameOfEntity(daughter->ID()) << ": Do Mom's role";

        break;

    case 1:

        cout << "\n" << GetNameOfEntity(daughter->ID()) << ": Do Dad's role";

        break;

    }
}

void PlayingDolls::Exit(MinersDaughter* daughter)
{
}

bool PlayingDolls::OnMessage(MinersDaughter* daughter, const Telegram& msg)
{
    return false;
}

//------------------------------------------------------------------------VisitBathroom

SleepingInRoom* SleepingInRoom::Instance()
{
    static SleepingInRoom instance;

    return &instance;
}


void SleepingInRoom::Enter(MinersDaughter* daughter)
{
    cout << "\n" << GetNameOfEntity(daughter->ID()) << ": I'm sleepy...";
}


void SleepingInRoom::Execute(MinersDaughter* daughter)
{
    cout << "\n" << GetNameOfEntity(daughter->ID()) << ": ZZZ...";

    daughter->GetFSM()->ChangeState(PlayingDolls::Instance());
}

void SleepingInRoom::Exit(MinersDaughter* daughter)
{
    cout << "\n" << GetNameOfEntity(daughter->ID()) << ": ZZZ...";
}


bool SleepingInRoom::OnMessage(MinersDaughter* daughter, const Telegram& msg)
{
    return false;
}


//------------------------------------------------------------------------CookStew

EatStewForDaughter* EatStewForDaughter::Instance()
{
    static EatStewForDaughter instance;

    return &instance;
}


void EatStewForDaughter::Enter(MinersDaughter* pDaughter)
{
    cout << "\n" << GetNameOfEntity(pDaughter->ID()) << ": " << "Eat Later!";
}

void EatStewForDaughter::Execute(MinersDaughter* pDaughter)
{
    cout << "\n" << GetNameOfEntity(pDaughter->ID()) << ": " << "Ahhhh! I don't want to eat this time";

    pDaughter->GetFSM()->RevertToPreviousState();
}

void EatStewForDaughter::Exit(MinersDaughter* pDaughter)
{
    cout << "\n" << GetNameOfEntity(pDaughter->ID()) << ": " << "I hate you!!";
}


bool EatStewForDaughter::OnMessage(MinersDaughter* pDaughter, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}