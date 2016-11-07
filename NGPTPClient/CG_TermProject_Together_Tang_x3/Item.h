#pragma once
#include "stdafx.h"
#include "Common.h"
class CItem
{
	Vec3		m_fPosition;
	int			m_iAngle;


public:
	void	Draw();
	void	Update();

public:
	CItem();
	~CItem();
};

