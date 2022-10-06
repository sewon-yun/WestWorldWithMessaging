#include "MinersBrother.h"

bool MinersBrother::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void MinersBrother::Update()
{
	//set text color to green
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}