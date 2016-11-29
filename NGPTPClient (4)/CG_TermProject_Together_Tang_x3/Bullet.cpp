#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}

CBullet::CBullet(float _fX, float _fY, float _fZ)
{
	m_fPos.fX = _fX;
	m_fPos.fY = _fY;
	m_fPos.fZ = _fZ;
}

CBullet::CBullet(float _fX, float _fY, float _fZ, float xTar, float yTar, float zTar/* float _fXrot, float _fYrot*/)
{
	m_fPos.fX = _fX;
	m_fPos.fY = _fY;
	m_fPos.fZ = _fZ;
	m_fDir.fX = xTar - m_fPos.fX;
	m_fDir.fY = yTar - m_fPos.fY;
	m_fDir.fZ = zTar - m_fPos.fZ;

	float len = sqrt(m_fDir.fX * m_fDir.fX + m_fDir.fY * m_fDir.fY + m_fDir.fZ * m_fDir.fZ);
	m_fDir.fX /= len;
	m_fDir.fY /= len;
	m_fDir.fZ /= len;

	m_fRotate.fX = 0;//_fXrot;
	m_fRotate.fY = 0;//_fYrot;
}


CBullet::~CBullet()
{
}

void CBullet::Update()
{
	if (m_fPos.fX < 0 || m_fPos.fZ < 0)
	{
		//this->Release();
	}
	//cout << "X " << m_fPos.fX << "Y " << m_fPos.fY << "Z " << m_fPos.fZ << endl;
	m_fPos.fX += m_fDir.fX * 50;
	m_fPos.fY += m_fDir.fY * 50;
	m_fPos.fZ += m_fDir.fZ * 50;

	if (m_fPosDistance <= 1000 || m_fPosDistance >= -1000)
		m_fPosDistance += m_fDir.fZ * 50;

	//cout << "ÃÑ¾Ë : " << m_fPos.fX << " " << m_fPos.fY << " " << m_fPos.fZ << endl;
}

Vec3 CBullet::GetPos()
{
	return m_fPos;
}

Vec3 CBullet::GetDirection()
{
	return m_fDir;
}

Vec2 CBullet::GetRotate()
{
	return m_fRotate;
}

int CBullet::GetPosDistance()
{
	return m_fPosDistance;
}

bool CBullet::ClearBullet()
{

	return false;
}

void CBullet::Release()
{
	delete this;
}
