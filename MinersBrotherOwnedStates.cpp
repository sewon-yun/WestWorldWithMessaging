#include "MinersBrotherOwnedStates.h"
#include "MinerOwnedStates.h"
#include "MinersBrother.h"
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

BrothersGlobalState* BrothersGlobalState::Instance()
{
    static BrothersGlobalState instance;

    return &instance;
}


void BrothersGlobalState::Execute(MinersBrother* brother)
{
    if ((RandFloat() < 0.1) &&
        !brother->GetFSM()->isInState(*WorkHard::Instance()))
    {
        brother->GetFSM()->ChangeState(WorkHard::Instance());
    }
}

bool BrothersGlobalState::OnMessage(MinersBrother* brother, const Telegram& msg)
{
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg)
    {
    case Msg_StewReady:
    {
        cout << "\nMessage handled by " << GetNameOfEntity(brother->ID()) << " at time: "
            << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        cout << "\n" << GetNameOfEntity(brother->ID()) <<
            ": Thank you for the meal!";

        brother->GetFSM()->ChangeState(EatStewForBrother::Instance());
        return true;
    }


    case Msg_TimeToPlay:
    {
        cout << "\nMessage handled by " << GetNameOfEntity(brother->ID()) << " at time: "
            << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

        cout << "\n" << GetNameOfEntity(brother->ID()) <<
            ": Alright, see you best keeper!!!";

        brother->GetFSM()->ChangeState(PlaySoccerWithNephew::Instance());
        return true;
    }



    }//end switch

    return false;
}

//-------------------------------------------------------------------------DoHouseWork

DoGame* DoGame::Instance()
{
    static DoGame instance;

    return &instance;
}


void DoGame::Enter(MinersBrother* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Wow is my life...";
}


void DoGame::Execute(MinersBrother* son)
{
    switch (RandInt(0, 3))
    {
    case 0:

        cout << "\n" << GetNameOfEntity(son->ID()) << ": Do Quest";

        break;

    case 1:

        cout << "\n" << GetNameOfEntity(son->ID()) << ": Do Raid";

        break;

    case 2:

        cout << "\n" << GetNameOfEntity(son->ID()) << ": Do PVP";

        break;
    case 3:

        cout << "\n" << GetNameOfEntity(son->ID()) << ": Do WebSurfing";

        break;
    }
}

void DoGame::Exit(MinersBrother* son)
{
}

bool DoGame::OnMessage(MinersBrother* son, const Telegram& msg)
{
    return false;
}

//------------------------------------------------------------------------VisitBathroom

WorkHard* WorkHard::Instance()
{
    static WorkHard instance;

    return &instance;
}


void WorkHard::Enter(MinersBrother* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Today's Work...";
}


void WorkHard::Execute(MinersBrother* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Loading trucks and stacking boxes";

    son->GetFSM()->ChangeState(DoGame::Instance());
}

void WorkHard::Exit(MinersBrother* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Reward is 100$";
}


bool WorkHard::OnMessage(MinersBrother* son, const Telegram& msg)
{
    return false;
}


//------------------------------------------------------------------------CookStew

PlaySoccerWithNephew* PlaySoccerWithNephew::Instance()
{
    static PlaySoccerWithNephew instance;

    return &instance;
}


void PlaySoccerWithNephew::Enter(MinersBrother* son)
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


void PlaySoccerWithNephew::Execute(MinersBrother* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Blocking";
}

void PlaySoccerWithNephew::Exit(MinersBrother* son)
{
    SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    cout << "\n" << GetNameOfEntity(son->ID()) << ": Sunsets in paradise, the end";
}


bool PlaySoccerWithNephew::OnMessage(MinersBrother* son, const Telegram& msg)
{
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg)
    {
    case Msg_SoccerReady:
    {
        cout << "\nMessage received by " << GetNameOfEntity(son->ID()) <<
            " at time: " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "\n" << GetNameOfEntity(son->ID()) << ": My Skill is God Hand";

        //let hubby know the stew is ready
        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
            son->ID(),
            ent_Miner_Bob,
            Msg_SoccerReady,
            NO_ADDITIONAL_INFO);

        son->SetPlayingSoccer(false);

        son->GetFSM()->ChangeState(DoGame::Instance());
    }

    return true;

    }//end switch

    return false;
}

EatStewForBrother* EatStewForBrother::Instance()
{
    static EatStewForBrother instance;

    return &instance;
}


void EatStewForBrother::Enter(MinersBrother* pSon)
{
    cout << "\n" << GetNameOfEntity(pSon->ID()) << ": " << "Let's Washing the hand!";
}

void EatStewForBrother::Execute(MinersBrother* pSon)
{
    cout << "\n" << GetNameOfEntity(pSon->ID()) << ": " << "Tastes good too!";

    pSon->GetFSM()->RevertToPreviousState();
}

void EatStewForBrother::Exit(MinersBrother* pSon)
{
    cout << "\n" << GetNameOfEntity(pSon->ID()) << ": " << "Go to wash the dish";
}


bool EatStewForBrother::OnMessage(MinersBrother* pSon, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}