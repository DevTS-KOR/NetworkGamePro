#pragma once
#include "stdafx.h"
#include "Common.h"
class CTimerManager
{
	DWORD		m_dwStartTime;
	DWORD		m_dwFrameTime;

public:
	size_t	GetFrameTime();

public:
	void	InitializeTime();
	void	Update();


public:
	CTimerManager();
	~CTimerManager();
};

