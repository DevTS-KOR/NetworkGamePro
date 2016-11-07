#pragma once
#include "stdafx.h"
#include "Common.h"
class CBullet
{
private:
	Vec3	m_fPos;
	Vec3	m_fDir;
	Vec2	m_fRotate;
public:
	void	Update();
	Vec3	GetPos();
	Vec3	GetDirection();
	Vec2	GetRotate();
	void	Release();
public:
	CBullet(float _fX, float _fY, float _fZ);
	CBullet(float _fX, float _fY, float _fZ, float xTar, float yTar, float zTar/* float _fXrot, float _fYrot*/);
	CBullet();
	~CBullet();
};


