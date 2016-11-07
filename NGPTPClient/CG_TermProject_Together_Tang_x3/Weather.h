#pragma once
#include "stdafx.h"
#include "Common.h"
class CWeather
{
	Vec3		m_tPosition;
	GLfloat		m_fSpeed;
	GLint		m_iTimer;
public:
	void	SetSpeed(float _Speed);
public:
	void	DrawWeather();
	void	Update();
	void	Initialize();
public:
	CWeather();
	~CWeather();
};

