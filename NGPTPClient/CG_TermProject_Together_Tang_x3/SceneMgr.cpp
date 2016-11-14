#include "stdafx.h"
#include "SceneMgr.h"
#include "Lobby.h"
#include "Logo.h"
#include "Scene.h"
#include "BitmapMgr.h"
#include "InGame.h"
#include "InResult.h"
CSceneMgr* CSceneMgr::m_pInst = NULL;

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

void CSceneMgr::SetScene(SceneList _eID, CBitmapMgr* _pBitmapMgr)
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
