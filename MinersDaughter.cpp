#include "MinersDaughter.h"

bool MinersDaughter::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void MinersDaughter::Update()
{
	SetTextColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}