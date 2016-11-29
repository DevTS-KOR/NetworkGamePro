#pragma once
#include "GameObject.h"
#include "BitmapMgr.h"
class CBuilding : public CGameObject
{
	BuildType	m_eType;
	CBitmapMgr*	m_pBitmapMgr;
	GLubyte * m_pMonster[4][36];
	GLubyte * m_pBuilding[3];
	GLubyte * m_pContainer[2];
public:
	virtual	GLvoid	Initialize();
	virtual	GLvoid	Draw();
	//virtual	GLvoid	Draw(MonsterList _eMonster);
	virtual	GLvoid	Update();
	virtual	bool	Collision();
	virtual GLvoid DrawCube(float fX, float fY, float fZ, float fWidth, float fHigh, float fDepth, GLubyte *pBytes[], float fXsize, float fYsize)override;
	GLvoid DrawCube(float fX, float fY, float fZ, float fWidth, float fHigh, float fDepth, GLubyte *pByte, float fXsize, float fYsize,int _type);
	GLvoid DrawContainer(float fX, float fY, float fZ, float fWidth, float fHigh, float fDepth, GLubyte **pByte, float fXsize, float fYsize, int _type);

	void drawBox(GLfloat size, GLenum type);
public:
	GLvoid	SetType(BuildType _eType);
public:
	CBuilding();
	CBuilding(CBitmapMgr* _pBitmapMgr);
	~CBuilding();
};
