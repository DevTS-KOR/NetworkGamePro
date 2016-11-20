#include "stdafx.h"
#include "SceneMgr.h"
#include "Lobby.h"
#include "Logo.h"
#include "Scene.h"
#include "BitmapMgr.h"
#include "InGame.h"
#include "InResult.h"
CSceneMgr* CSceneMgr::m_pInst = NULL;
InitInfo* CSceneMgr::strInitInfo = NULL;
SceneInfo* CSceneMgr::strSceneInfo = NULL;
MonsterPosForRecv* CSceneMgr::strMonsterPos = NULL;

CSceneMgr::CSceneMgr() :m_pScene(NULL)
{
	/*if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		err_quit("WSAStartup");

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
		err_quit("connect()");*/
}


CSceneMgr::~CSceneMgr()
{
	
}

void CSceneMgr::SetScene(int _eID, CBitmapMgr* _pBitmapMgr)
{
	if (m_pScene != NULL)
		::Safe_Delete(m_pScene);
	
	switch (_eID)
	{
	case SCENE_LOGO:
		m_pScene = new CLogo;
		break;
	case SCENE_LOBBY:
		m_pScene = new CLobby;
		break;
	case SCENE_INGAME:
		m_pScene = new CInGame;
		break;
	case SCENE_INRESULT:
		m_pScene = new InResult;
	case SCENE_NONE:
		break;
	default:
		break;
	}
	m_pScene->Initialize(_pBitmapMgr);
}

void CSceneMgr::RecvInitInfo()
{
	int retval;
	char buf[BUFSIZE];

	retval = recv(sock, buf, sizeof(InitInfo), 0);
	if (retval == SOCKET_ERROR)
		err_quit("recv()");

	tempInitInfo = (InitInfo&)buf;
	strInitInfo = &tempInitInfo;
	printf("%d바이트 받음\n", retval);

	//printf("위치위치 마녀는 영어로 위치 %f\n", strInitInfo->MonsterPos[4].fY);

}

InitInfo* CSceneMgr::GetInitInfo()
{
	return strInitInfo;
}

void CSceneMgr::SendSpace()
{
	int retval;
	char buf[BUFSIZE];

	retval = send(sock, buf, sizeof(buf), 0);
	if (retval == SOCKET_ERROR)
		err_quit("send()");
}

void CSceneMgr::RecvSpace()
{
	int retval;
	char buf[BUFSIZE];

	retval = recv(sock, buf, sizeof(SceneInfo), 0);
	if (retval == SOCKET_ERROR)
		err_quit("recv()");

	tempSceneInfo = (SceneInfo&)buf;
	strSceneInfo = &tempSceneInfo;
}

SceneInfo * CSceneMgr::GetSceneInfo()
{
	return strSceneInfo;
}

void CSceneMgr::SetMonsterPos()
{
	//cout << "받았어요1" << endl;
	int retval;
	char buf[BUFSIZE];

	retval = recv(sock, buf, sizeof(MonsterPosForRecv), 0);
	if (retval == SOCKET_ERROR)
		err_quit("recv()");

	//cout << "받았어요2" << endl;
	tempMonsterPos = (MonsterPosForRecv&)buf;
	strMonsterPos = &tempMonsterPos;

}

MonsterPosForRecv* CSceneMgr::GetMonsterPos()
{
	return strMonsterPos;
}


GLvoid CSceneMgr::Render(GLvoid)
{
	m_pScene->Render();
}

GLvoid CSceneMgr::Keyboard(unsigned char key, int x, int y)
{
	m_pScene->Keyboard(key, x, y);
}

GLvoid	CSceneMgr::KeyboardUp(unsigned char key, int x, int y)
{
	m_pScene->KeyboardUp(key, x, y);
}

GLvoid CSceneMgr::SpecialKeyboard(int key, int x, int y)
{
	m_pScene->SpecialKeyboard(key, x, y);
}

GLvoid CSceneMgr::SpecialKeyboardUp(int key, int x, int y)
{
	m_pScene->SpecialKeyboardUp(key, x, y);
}

void CSceneMgr::err_quit(char * msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

void CSceneMgr::err_display(char * msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

GLvoid CSceneMgr::ConnectServer()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		err_quit("WSAStartup");

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
		err_quit("connect()");
}



GLvoid CSceneMgr::Update(int value)
{
	m_pScene->Update(value);
}

GLvoid CSceneMgr::Mouse(int button, int state, int x, int y)
{
	m_pScene->Mouse(button, state, x, y);
}

GLvoid CSceneMgr::MouseMotionFunc(int x, int y)
{
	m_pScene->MouseMotionFunc( x, y);
}

GLvoid CSceneMgr::Release()
{
	::Safe_Delete(m_pScene);
}

CSceneMgr* CSceneMgr::GetInst(void)
{
	if (m_pInst == NULL)
		m_pInst = new CSceneMgr;

	return m_pInst;
}

void CSceneMgr::DestroyInst(void)
{
	delete m_pInst;
	m_pInst = NULL;
}
