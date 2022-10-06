#include "MinersSonOwnedStates.h"
#include "MinerOwnedStates.h"
#include "MinersSon.h"
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

SonsGlobalState* SonsGlobalState::Instance()
{
    static SonsGlobalState instance;

    return &instance;
}


void SonsGlobalState::Execute(MinersSon* son)
{
    //1 in 10 chance of needing the bathroom (provided she is not already
    //in the bathroom)
    if ((RandFloat() < 0.1) &&
        !son->GetFSM()->isInState(*VisitBathroom1::Instance()))
    {
        son->GetFSM()->ChangeState(VisitBathroom1::Instance());
    }
}

bool SonsGlobalState::OnMessage(MinersSon* son, const Telegram& msg)
{
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg)
    {
    case Msg_HiHoneyImHome:
    {
        cout << "\nMessage handled by " << GetNameOfEntity(son->ID()) << " at time: "
            << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        cout << "\n" << GetNameOfEntity(son->ID()) <<
            ": Hi honey. Let me make you some of mah fine country stew";

        son->GetFSM()->ChangeState(CookStew1::Instance());
    }

    return true;

    }//end switch

    return false;
}

//-------------------------------------------------------------------------DoHouseWork

DoHouseWork1* DoHouseWork1::Instance()
{
    static DoHouseWork1 instance;

    return &instance;
}


void DoHouseWork1::Enter(MinersSon* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Time to do some more housework!";
}


void DoHouseWork1::Execute(MinersSon* son)
{
    switch (RandInt(0, 2))
    {
    case 0:

        cout << "\n" << GetNameOfEntity(son->ID()) << ": Moppin' the floor";

        break;

    case 1:

        cout << "\n" << GetNameOfEntity(son->ID()) << ": Washin' the dishes";

        break;

    case 2:

        cout << "\n" << GetNameOfEntity(son->ID()) << ": Makin' the bed";

        break;
    }
}

void DoHouseWork1::Exit(MinersSon* son)
{
}

bool DoHouseWork1::OnMessage(MinersSon* son, const Telegram& msg)
{
    return false;
}

//------------------------------------------------------------------------VisitBathroom

VisitBathroom1* VisitBathroom1::Instance()
{
    static VisitBathroom1 instance;

    return &instance;
}


void VisitBathroom1::Enter(MinersSon* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Walkin' to the can. Need to powda mah pretty li'lle nose";
}


void VisitBathroom1::Execute(MinersSon* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Ahhhhhh! Sweet relief!";

    son->GetFSM()->RevertToPreviousState();
}

void VisitBathroom1::Exit(MinersSon* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Leavin' the Jon";
}


bool VisitBathroom1::OnMessage(MinersSon* son, const Telegram& msg)
{
    return false;
}


//------------------------------------------------------------------------CookStew

CookStew1* CookStew1::Instance()
{
    static CookStew1 instance;

    return &instance;
}


void CookStew1::Enter(MinersSon* son)
{
    //if not already cooking put the stew in the oven
    if (!son->Cooking())
    {
        cout << "\n" << GetNameOfEntity(son->ID()) << ": Putting the stew in the oven";

        //send a delayed message myself so that I know when to take the stew
        //out of the oven
        Dispatch->DispatchMessage(1.5,                  //time delay
            son->ID(),           //sender ID
            son->ID(),           //receiver ID
            Msg_StewReady,        //msg
            NO_ADDITIONAL_INFO);

        son->SetCooking(true);
    }
}


void CookStew1::Execute(MinersSon* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Fussin' over food";
}

void CookStew1::Exit(MinersSon* son)
{
    SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    cout << "\n" << GetNameOfEntity(son->ID()) << ": Puttin' the stew on the table";
}


bool CookStew1::OnMessage(MinersSon* son, const Telegram& msg)
{
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg)
    {
    case Msg_StewReady:
    {
        cout << "\nMessage received by " << GetNameOfEntity(son->ID()) <<
            " at time: " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "\n" << GetNameOfEntity(son->ID()) << ": StewReady! Lets eat";

        //let hubby know the stew is ready
        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
            son->ID(),
            ent_Miner_Bob,
            Msg_StewReady,
            NO_ADDITIONAL_INFO);

        son->SetCooking(false);

        son->GetFSM()->ChangeState(DoHouseWork1::Instance());
    }

    return true;

    }//end switch

    return false;
}