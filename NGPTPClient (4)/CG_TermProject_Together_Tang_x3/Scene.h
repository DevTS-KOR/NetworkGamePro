#pragma once
#include "stdafx.h"

class CBitmapMgr;
class CScene
{
protected:
	GLuint      m_iTextures;
	CBitmapMgr* m_pBitmapMgr;
	DWORD		m_dwTime;
	HANDLE		hThread;
public:
	virtual	GLvoid	Initialize(CBitmapMgr* _pBitmapMgr) = 0;
	virtual GLvoid	Render         (GLvoid) = 0;
	virtual GLvoid	Keyboard       (unsigned char key, int x, int y) = 0;
	virtual GLvoid	KeyboardUp(unsigned char key, int x, int y) = 0;
	virtual GLvoid	SpecialKeyboard(int key, int x, int y) = 0;
	virtual GLvoid	SpecialKeyboardUp(int key, int x, int y) = 0;
	virtual GLvoid	Update         (int value) = 0;
	virtual GLvoid	Mouse          (int button, int state, int x, int y) = 0;
	virtual GLvoid	MouseMotionFunc(int x, int y) = 0;
	virtual GLvoid	Release        (GLvoid) = 0;

public:
	CScene();
	~CScene();
};

