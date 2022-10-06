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


void DaughtersGlobalState::Execute(MinersDaughter* son)
{
    //1 in 10 chance of needing the bathroom (provided she is not already
    //in the bathroom)
    if ((RandFloat() < 0.1) &&
        !son->GetFSM()->isInState(*SleepingInRoom::Instance()))
    {
        son->GetFSM()->ChangeState(SleepingInRoom::Instance());
    }
}

bool DaughtersGlobalState::OnMessage(MinersDaughter* son, const Telegram& msg)
{
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg)
    {
    case Msg_StewReady:
    {
        cout << "\nMessage handled by " << GetNameOfEntity(son->ID()) << " at time: "
            << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_BLUE && FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        cout << "\n" << GetNameOfEntity(son->ID()) <<
            ": I'm busy, eat later!";

        son->GetFSM()->ChangeState(EatStewForDaughter::Instance());
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


void PlayingDolls::Enter(MinersDaughter* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Where's my Bobby!!";
}


void PlayingDolls::Execute(MinersDaughter* son)
{
    switch (RandInt(0, 1))
    {
    case 0:

        cout << "\n" << GetNameOfEntity(son->ID()) << ": Do Mom's role";

        break;

    case 1:

        cout << "\n" << GetNameOfEntity(son->ID()) << ": Do Dad's role";

        break;

    }
}

void PlayingDolls::Exit(MinersDaughter* son)
{
}

bool PlayingDolls::OnMessage(MinersDaughter* son, const Telegram& msg)
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

    daughter->GetFSM()->RevertToPreviousState();
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