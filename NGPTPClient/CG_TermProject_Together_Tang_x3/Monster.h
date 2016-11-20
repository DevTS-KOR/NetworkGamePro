#pragma once
#include "GameObject.h"
#include "BitmapMgr.h"
#include "Bullet.h"
class CCharacter;
class CMonster : public CGameObject
{
	Vec3	Monster_Vec;
	float fZ_left_arm;
	float fZ_right_arm;
	float fZ_left_leg;
	float fZ_right_leg;
	float fArm_move;
	float fLeg_move;
	GLubyte * m_pMonster[4][36];
	CBitmapMgr*	m_pBitmapMgr;
	MonsterList m_eMonterType;
	static int  m_MonsterList;

	vector<CBullet>* m_vpBullet;
	float  m_fAngle;
public:
	CMonster();
	CMonster(CBitmapMgr* _pBitmapMgr);
	CMonster(CBitmapMgr* _pBitmapMgr, float _fX,float _fZ);
	~CMonster();

	virtual GLvoid Initialize()override;
	virtual GLvoid Draw()override;
	GLvoid Draw(MonsterList _eMonster);
	virtual GLvoid Update()override;
	virtual bool Collision()override;
	virtual GLvoid DrawCube(float fX, float fY, float fZ, float fWidth, float fHigh, float fDepth, GLubyte *pBytes[], float fXsize, float fYsize)override;

public:
	bool Collision(double _targetX, double _targetY, double _targetZ, double _targetRad);
	bool Collision(vector<CBullet>& _vpBullet, double _targetRad);
	void	Chase(CCharacter*_pCharacter);
	
public:
	Vec3	GetPosition();
	void	SetPosition(Vec3 _Position);
};

