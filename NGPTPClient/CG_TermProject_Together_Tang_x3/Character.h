#pragma once
#include "stdafx.h"
#include "Common.h"
#include "GameObject.h"
#include "BitmapMgr.h"
class CCharacter : public CGameObject
{
	bool			m_bIsSniperMode;
	float			m_fSniper;
	Vec3			m_fCameraPos;
	Vec3			m_fCameraRotate;
	GLubyte*		m_pPlayer[1][36];
	CBitmapMgr*		m_pBitmapMgr;
	PlayerList		m_ePlayerType;
	InitInfo*		m_InitInfo;
	float fZ_left_arm;
	float fZ_right_arm;
	float fZ_left_leg;
	float fZ_right_leg;
	float fArm_move;
	float fLeg_move;

	int				m_iCameradistance;
	bool			m_bKeyUpState[4];
public:
	CCharacter(CBitmapMgr* _pBitmapMgr);
	CCharacter(CBitmapMgr* _pBitmapMgr, float _fX1, float _fZ1, float _fX2, float _fZ2);

	~CCharacter();

	virtual GLvoid Initialize();
	virtual GLvoid Draw();
	virtual GLvoid Update();
	virtual bool Collision();
	virtual GLvoid DrawCube(float fX, float fY, float fZ, float fWidth, float fHigh, float fDepth, GLubyte *pBytes[], float fXsize, float fYsize);
public:
	GLfloat	GetSpeed();
	Vec3	GetPosition();
	Vec3	GetCameraRotate();
	Vec3	GetCameraPos();
	float	GetSniper();
	bool	GetSniperMode();
	bool	GetKeyUpState(KeyUpState _eState);
	int		GetCameraDistance();
public:
	void	SetSniper(float _fSniper);
	void	SetSniperMode(bool _bMode);
	void	SetKeyUpstate(KeyUpState _eState, bool _bState);
	void	SetCameraPos(float _fPos,int _Type);
	void	SetCameraRotate(float _fPos, int _Type);
	void	SetCameraDistance(int _iDistance);
	void	SetCharPosition(InitInfo* _InitInfo);
	//void	SetCameraRotate(float _fX, float _fY, float _fZ);


};

