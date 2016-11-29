#include "stdafx.h"
#include "TimerManager.h"


CTimerManager::CTimerManager()
{
}


CTimerManager::~CTimerManager()
{
}

void CTimerManager::InitializeTime()
{

}

size_t CTimerManager::GetFrameTime()
{
	return m_dwFrameTime;
}

void CTimerManager::Update()
{
	m_dwFrameTime = GetTickCount() - m_dwStartTime;
	m_dwStartTime = GetTickCount();
}
