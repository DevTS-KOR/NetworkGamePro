#pragma once
#include "Scene.h"
class CLobby : public CScene
{
	/*GLuint      m_iTextures;
	CBitmapMgr* m_pBitmapMgr;
	DWORD		m_dwTime;*/
public:
	virtual	GLvoid	Initialize(CBitmapMgr* _pBitmapMgr);
	virtual GLvoid	Render(GLvoid);
	virtual GLvoid	Keyboard(unsigned char key, int x, int y);
	virtual GLvoid	SpecialKeyboard(int key, int x, int y);
	virtual GLvoid	Update(int value);
	virtual GLvoid	Mouse(int button, int state, int x, int y);
	virtual GLvoid	MouseMotionFunc(int x, int y);
	virtual GLvoid	Release();


public:
	CLobby();
	~CLobby();

	virtual GLvoid SpecialKeyboardUp(int key, int x, int y);

	virtual GLvoid KeyboardUp(unsigned char key, int x, int y);

};

