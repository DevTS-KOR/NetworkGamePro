#pragma once
#include "stdafx.h"
#include "Common.h"
#include "GameObject.h"

class CBunker : public CGameObject
{
	
public:
	virtual GLvoid	Draw();
	//virtual	GLvoid	Draw(MonsterList _eMonster);
	virtual GLvoid	Initialize();
	virtual GLvoid	Update();
	virtual bool	Collision();
public:
	CBunker();
	~CBunker();


};

