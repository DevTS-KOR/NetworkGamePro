#pragma once
#include "stdafx.h"
#include "Common.h"
class CScene;
class CBitmapMgr;
class CGameObject;
class CCharacter;
class CSceneMgr
{
	static CSceneMgr*		m_pInst;
	CScene*					m_pScene;
	CGameObject*			m_pCharacter;
	// ���� �ʱ�ȭ
	WSADATA					wsa;
	// socket()
	SOCKET					sock;
	// connect()
	SOCKADDR_IN				serveraddr;
	int						retval;
	/////////////////////////////////////////////
	static InitInfo*		strInitInfo;
	InitInfo				tempInitInfo;

	static SceneInfo*		strSceneInfo;
	SceneInfo				tempSceneInfo;

	static MonsterPosForRecv*	strMonsterPos;
	static PlayerInfo*			strPlayerInfo;


	static unsigned char	charKey;
	PlayerInfo				tempPlayerInfo;
public:
	void SetScene(int _eID, CBitmapMgr* _pBitmapMgr);

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
	SOCKET GetSocket();

	void RecvInitInfo();
	static InitInfo* GetInitInfo();
	
	void SendSpace();
	void RecvSpace();
	static SceneInfo* GetSceneInfo();

	void RecvServer();
	static MonsterPosForRecv* GetMonsterPos();

	static PlayerInfo* GetPlayerPos();
	int recvn(SOCKET s, char* buf, int len, int flags);

	static void SetKey(unsigned char _Key);
	void SendInfo(Vec3 _Position, float _RotateCamera);
	void SendNull();
	void RecvKey();
	void SetCharClass(CGameObject* _pChar)
	{
		m_pCharacter = _pChar;
	}
	//void PlayerRender();
	//void MonsterRender();
	//void ContainerRender();
public:
	CSceneMgr();
	~CSceneMgr();
	
};

