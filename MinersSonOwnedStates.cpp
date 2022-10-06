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
    if ((RandFloat() < 0.1) &&
        !son->GetFSM()->isInState(*VisitBathRoomSon::Instance()))
    {
        son->GetFSM()->ChangeState(VisitBathRoomSon::Instance());
    }
}

bool SonsGlobalState::OnMessage(MinersSon* son, const Telegram& msg)
{
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg)
    {
    case Msg_StewReady:
    {
        cout << "\nMessage handled by " << GetNameOfEntity(son->ID()) << " at time: "
            << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

        cout << "\n" << GetNameOfEntity(son->ID()) <<
            ": Thank you for the meal!";

        son->GetFSM()->ChangeState(EatStewForSon::Instance());
        return true;
    }
    case Msg_TimeToPlay:
    {
        cout << "\nMessage handled by " << GetNameOfEntity(son->ID()) << " at time: "
            << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

        cout << "\n" << GetNameOfEntity(son->ID()) <<
            ": Hi Uncle, Let's Play Soccer!!";

        son->GetFSM()->ChangeState(PlaySoccer::Instance());
        return true;
    }
    }//end switch

    return false;
}

//-------------------------------------------------------------------------DoHouseWork

DoHomework* DoHomework::Instance()
{
    static DoHomework instance;

    return &instance;
}


void DoHomework::Enter(MinersSon* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Time to homework.. Fighting!!";
}


void DoHomework::Execute(MinersSon* son)
{
    switch (RandInt(0, 2))
    {
    case 0:

        cout << "\n" << GetNameOfEntity(son->ID()) << ": Do math homework";

        break;

    case 1:

        cout << "\n" << GetNameOfEntity(son->ID()) << ": Do science homework";

        break;

    case 2:

        cout << "\n" << GetNameOfEntity(son->ID()) << ": Snooze";

        break;
    }
}

void DoHomework::Exit(MinersSon* son)
{
}

bool DoHomework::OnMessage(MinersSon* son, const Telegram& msg)
{
    return false;
}

//------------------------------------------------------------------------VisitBathroom

VisitBathRoomSon* VisitBathRoomSon::Instance()
{
    static VisitBathRoomSon instance;

    return &instance;
}


void VisitBathRoomSon::Enter(MinersSon* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Today is really hot day";
}


void VisitBathRoomSon::Execute(MinersSon* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Washing body";

    son->GetFSM()->ChangeState(DoHomework::Instance());
}

void VisitBathRoomSon::Exit(MinersSon* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Sweeping body";
}


bool VisitBathRoomSon::OnMessage(MinersSon* son, const Telegram& msg)
{
    return false;
}


//------------------------------------------------------------------------CookStew

PlaySoccer* PlaySoccer::Instance()
{
    static PlaySoccer instance;

    return &instance;
}


void PlaySoccer::Enter(MinersSon* son)
{
    //if not already cooking put the stew in the oven
    if (!son->PlayingSoccer())
    {
        cout << "\n" << GetNameOfEntity(son->ID()) << ": Putting a ball in the ground";

        //send a delayed message myself so that I know when to take the stew
        //out of the oven
        Dispatch->DispatchMessage(1.5,                  //time delay
            son->ID(),           //sender ID
            son->ID(),           //receiver ID
            Msg_SoccerReady,        //msg
            NO_ADDITIONAL_INFO);

        son->SetPlayingSoccer(true);
    }
}


void PlaySoccer::Execute(MinersSon* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Dribbling";
}

void PlaySoccer::Exit(MinersSon* son)
{
    SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    cout << "\n" << GetNameOfEntity(son->ID()) << ": Thank you for playing soccer with me, uncle!";
}


bool PlaySoccer::OnMessage(MinersSon* son, const Telegram& msg)
{
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg)
    {
    case Msg_SoccerReady:
    {
        cout << "\nMessage received by " << GetNameOfEntity(son->ID()) <<
            " at time: " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "\n" << GetNameOfEntity(son->ID()) << ": My dribble is Heung-min Son grade, uncle";

        son->SetPlayingSoccer(false);

        son->GetFSM()->ChangeState(DoHomework::Instance());
    }

    return true;

    }//end switch

    return false;
}

EatStewForSon* EatStewForSon::Instance()
{
    static EatStewForSon instance;

    return &instance;
}


void EatStewForSon::Enter(MinersSon* pSon)
{
    cout << "\n" << GetNameOfEntity(pSon->ID()) << ": " << "Really good smells mom!";
}

void EatStewForSon::Execute(MinersSon* pSon)
{
    cout << "\n" << GetNameOfEntity(pSon->ID()) << ": " << "Tastes good too!";

    pSon->GetFSM()->RevertToPreviousState();
}

void EatStewForSon::Exit(MinersSon* pSon)
{
    cout << "\n" << GetNameOfEntity(pSon->ID()) << ": " << "Thank you for make the meel! I love you, mom";
}


bool EatStewForSon::OnMessage(MinersSon* pSon, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}