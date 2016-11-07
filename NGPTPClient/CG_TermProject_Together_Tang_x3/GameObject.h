#pragma once
#include "stdafx.h"
#include "Common.h"

class CGameObject
{
protected:
	Vec3		m_tPosition;
	ColorAlpha	m_tColor;
	GLfloat		m_fSpeed;
	GLfloat		m_fRotate;
	GLfloat		m_fScale;

public:
	virtual	GLvoid	Initialize() = 0;
	virtual	GLvoid	Draw() = 0;
	virtual	GLvoid	Update() = 0;
	virtual	bool	Collision() = 0;
	virtual GLvoid	DrawCube(float fX, float fY, float fZ, float fWidth, float fHigh, float fDepth, GLubyte *pBytes[], float fXsize, float fYsize)=0;
public:
	CGameObject();
	~CGameObject();
};

