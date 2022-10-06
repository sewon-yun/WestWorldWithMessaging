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
            ": Hi Daddy, Let's Play Soccer!!";

        son->GetFSM()->ChangeState(PlaySoccer::Instance());
        return true;
    }



    }//end switch

    return false;
}

//-------------------------------------------------------------------------DoHouseWork

DoHomeWork* DoHomeWork::Instance()
{
    static DoHomeWork instance;

    return &instance;
}


void DoHomeWork::Enter(MinersSon* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Time to do homework!, I Really hate homework...";
}


void DoHomeWork::Execute(MinersSon* son)
{
    switch (RandInt(0, 2))
    {
    case 0:

        cout << "\n" << GetNameOfEntity(son->ID()) << ": Do math";

        break;

    case 1:

        cout << "\n" << GetNameOfEntity(son->ID()) << ": Do science";

        break;

    case 2:

        cout << "\n" << GetNameOfEntity(son->ID()) << ": Snooze";

        break;
    }
}

void DoHomeWork::Exit(MinersSon* son)
{
}

bool DoHomeWork::OnMessage(MinersSon* son, const Telegram& msg)
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
    cout << "\n" << GetNameOfEntity(son->ID()) << ": I want to shower";
}


void VisitBathroom1::Execute(MinersSon* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Wow! Very cold... where's the warm water?";

    son->GetFSM()->RevertToPreviousState();
}

void VisitBathroom1::Exit(MinersSon* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Sweep my body";
}


bool VisitBathroom1::OnMessage(MinersSon* son, const Telegram& msg)
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
        cout << "\n" << GetNameOfEntity(son->ID()) << ": Putting the bool in the ground";

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
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Dribble the ball";
}

void PlaySoccer::Exit(MinersSon* son)
{
    SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    cout << "\n" << GetNameOfEntity(son->ID()) << ": I'm tired, byebye";
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
        cout << "\n" << GetNameOfEntity(son->ID()) << ": Lets go! I'm heungmin Son";

        //let hubby know the stew is ready
        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
            son->ID(),
            ent_Miner_Bob,
            Msg_SoccerReady,
            NO_ADDITIONAL_INFO);

        son->SetPlayingSoccer(false);

        son->GetFSM()->ChangeState(DoHomeWork::Instance());
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
    cout << "\n" << GetNameOfEntity(pSon->ID()) << ": " << "Smells Reaaal goood Elsa!";
}

void EatStewForSon::Execute(MinersSon* pSon)
{
    cout << "\n" << GetNameOfEntity(pSon->ID()) << ": " << "Tastes real good too!";

    pSon->GetFSM()->RevertToPreviousState();
}

void EatStewForSon::Exit(MinersSon* pSon)
{
    cout << "\n" << GetNameOfEntity(pSon->ID()) << ": " << "Thank you mom";
}


bool EatStewForSon::OnMessage(MinersSon* pSon, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}