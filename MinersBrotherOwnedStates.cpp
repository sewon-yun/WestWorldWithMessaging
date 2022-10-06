#include "MinersBrotherOwnedStates.h"
#include "MinerOwnedStates.h"
#include "MinersBrother.h"
#include "Locations.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"
#include "MinersWife.h"
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

    }//end switch

    return false;
}

//-------------------------------------------------------------------------DoHouseWork

DoGame* DoGame::Instance()
{
    static DoGame instance;

    return &instance;
}


void DoGame::Enter(MinersBrother* brother)
{
    cout << "\n" << GetNameOfEntity(brother->ID()) << ": Wow is my life...";
}


void DoGame::Execute(MinersBrother* brother)
{
    switch (RandInt(0, 3))
    {
    case 0:

        cout << "\n" << GetNameOfEntity(brother->ID()) << ": Do Quest";

        break;

    case 1:

        cout << "\n" << GetNameOfEntity(brother->ID()) << ": Do Raid";

        break;

    case 2:

        cout << "\n" << GetNameOfEntity(brother->ID()) << ": Do PVP";

        break;
    case 3:

        cout << "\n" << GetNameOfEntity(brother->ID()) << ": Do WebSurfing";

        break;
    }
}

void DoGame::Exit(MinersBrother* brother)
{
}

bool DoGame::OnMessage(MinersBrother* brother, const Telegram& msg)
{
    return false;
}

//------------------------------------------------------------------------VisitBathroom

WorkHard* WorkHard::Instance()
{
    static WorkHard instance;

    return &instance;
}


void WorkHard::Enter(MinersBrother* brother)
{
    cout << "\n" << GetNameOfEntity(brother->ID()) << ": Today's Work...";
}


void WorkHard::Execute(MinersBrother* brother)
{
    cout << "\n" << GetNameOfEntity(brother->ID()) << ": Loading trucks and stacking boxes";
    brother->GetFSM()->ChangeState(PlaySoccerWithNephew::Instance());

    Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
        brother->ID(),        //ID of sender
        ent_Evan,            //ID of recipient
        Msg_TimeToPlay,     //the message
        NO_ADDITIONAL_INFO);
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


void PlaySoccerWithNephew::Enter(MinersBrother* brother)
{
    //if not already cooking put the stew in the oven
    if (!brother->PlayingSoccer())
    {
        cout << "\n" << GetNameOfEntity(brother->ID()) << ": Drive Car in the ground";

        //send a delayed message myself so that I know when to take the stew
        //out of the oven
        Dispatch->DispatchMessage(1.5,                  //time delay
            brother->ID(),           //sender ID
            brother->ID(),           //receiver ID
            Msg_SoccerReady,        //msg
            NO_ADDITIONAL_INFO);

        brother->SetPlayingSoccer(true);
    }
}


void PlaySoccerWithNephew::Execute(MinersBrother* son)
{
    cout << "\n" << GetNameOfEntity(son->ID()) << ": Blocking";
}

void PlaySoccerWithNephew::Exit(MinersBrother* son)
{
    SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    cout << "\n" << GetNameOfEntity(son->ID()) << ": Sunsets in paradise, the end";
}


bool PlaySoccerWithNephew::OnMessage(MinersBrother* brother, const Telegram& msg)
{
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg)
    {
    case Msg_SoccerReady:
    {
        cout << "\nMessage received by " << GetNameOfEntity(brother->ID()) <<
            " at time: " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "\n" << GetNameOfEntity(brother->ID()) << ": My Skill is God Hand";

        brother->SetPlayingSoccer(false);

        brother->GetFSM()->ChangeState(DoGame::Instance());
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


void EatStewForBrother::Enter(MinersBrother* pBrother)
{
    cout << "\n" << GetNameOfEntity(pBrother->ID()) << ": " << "Let's Washing the hand!";
}

void EatStewForBrother::Execute(MinersBrother* pBrother)
{
    cout << "\n" << GetNameOfEntity(pBrother->ID()) << ": " << "Tastes good too!";

    pBrother->GetFSM()->RevertToPreviousState();
}

void EatStewForBrother::Exit(MinersBrother* pBrother)
{
    cout << "\n" << GetNameOfEntity(pBrother->ID()) << ": " << "Go to wash the dish";
}


bool EatStewForBrother::OnMessage(MinersBrother* pBrother, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}