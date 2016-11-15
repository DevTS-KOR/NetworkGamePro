#pragma once
#include "stdafx.h"
#include "Common.h"
class CScene;
class CBitmapMgr;
class CSceneMgr
{
	static CSceneMgr*		m_pInst;
	CScene*					m_pScene;
	// ���� �ʱ�ȭ
	WSADATA					wsa;
	// socket()
	SOCKET					sock;
	// connect()
	SOCKADDR_IN				serveraddr;
	int						retval;
	/////////////////////////////////////////////
	InitInfo strInitInfo;
public:
	void SetScene(SceneList _eID, CBitmapMgr* _pBitmapMgr);

public:
	static CSceneMgr* GetInst(void);

	void DestroyInst(void);
public:
	GLvoid	Render(GLvoid);
	GLvoid	KeyboardUp(unsigned char key, int x, int y);
	GLvoid	Keyboard(unsigned char key, int x, int y);
	GLvoid	SpecialKeyboard(int key, int x, int y);
	GLvoid	Update(int value);
	GLvoid	Mouse(int button, int state, int x, int y);
	GLvoid	MouseMotionFunc(int x, int y);
	GLvoid	Release();
	GLvoid	SpecialKeyboardUp(int key, int x, int y);
	// ���� �Լ� ���� ��� �� ����
	void err_quit(char *msg);
	// ���� �Լ� ���� ���
	void err_display(char *msg);
	GLvoid ConnectServer();
	void RecvInitInfo(InitInfo _InitInfo);
public:
	CSceneMgr();
	~CSceneMgr();
	
};

