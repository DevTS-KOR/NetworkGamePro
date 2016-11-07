#pragma once
#include "Scene.h"
class InResult : public CScene
{

public:
	virtual	GLvoid	Initialize(CBitmapMgr* _pBitmapMgr);
	virtual GLvoid	Render(GLvoid);
	virtual GLvoid	Keyboard(unsigned char key, int x, int y);
	virtual GLvoid	SpecialKeyboard(int key, int x, int y);
	virtual GLvoid	Update(int value);
	virtual GLvoid	Mouse(int button, int state, int x, int y);
	virtual GLvoid	MouseMotionFunc(int x, int y);
	virtual GLvoid	Release();

	virtual GLvoid SpecialKeyboardUp(int key, int x, int y);

	virtual GLvoid KeyboardUp(unsigned char key, int x, int y);
public:
	InResult();
	~InResult();
};

