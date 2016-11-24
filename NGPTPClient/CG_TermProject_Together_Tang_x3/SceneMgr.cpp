#include "stdafx.h"
#include "SceneMgr.h"
#include "Lobby.h"
#include "Logo.h"
#include "Scene.h"
#include "BitmapMgr.h"
#include "InGame.h"
#include "InResult.h"
#include "GameObject.h"
#include "Character.h"
CSceneMgr* CSceneMgr::m_pInst = NULL;
InitInfo* CSceneMgr::strInitInfo = NULL;
SceneInfo* CSceneMgr::strSceneInfo = NULL;
MonsterPosForRecv* CSceneMgr::strMonsterPos = NULL;
PlayerInfo* CSceneMgr::strPlayerInfo = NULL;
unsigned char CSceneMgr::charKey = 0;

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

	retval = recv(sock, (char*)&tempInitInfo, sizeof(InitInfo), 0);
	if (retval == SOCKET_ERROR)
		err_quit("recv()");

	//tempInitInfo = (InitInfo&)buf;
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

void CSceneMgr::RecvServer()
{
	int retval;
	int dataType = 0;
	MonsterPosForRecv		tempMonsterPos;
	PlayerInfo				tempInfo;

	while (true)
	{
		retval = recv(sock, (char*)&dataType, sizeof(int), 0);
		if (retval == SOCKET_ERROR)
			err_quit("recv()");

		if (dataType == DataType::PLAYER)
		{
			retval = recv(sock, (char*)&tempInfo, sizeof(PlayerInfo), 0);
			if (retval == SOCKET_ERROR)
				err_quit("recv()");

			strPlayerInfo = &tempInfo;
			cout << "받은 인덱스 : " << strPlayerInfo->playerIndex << endl;
			cout << "받은값 : " << strPlayerInfo->PlayerPos.fX << ", " << strPlayerInfo->PlayerPos.fY << ", " << strPlayerInfo->PlayerPos.fZ << endl << endl;
			dynamic_cast<CCharacter*>(m_pCharacter)->SetCharRecvPosition(GetInitInfo(), GetPlayerPos());
		}

		else if (dataType == DataType::MONSTER)
		{
			//cout << "니가1" << endl;

			retval = recv(sock, (char*)&tempMonsterPos, sizeof(MonsterPosForRecv), 0);
			if (retval == SOCKET_ERROR)
				err_quit("recv()");

			strMonsterPos = &tempMonsterPos;

			//cout << "니가2" << endl << endl;
		}

		else
		{
			char buf[BUFSIZE];
			retval = recvn(sock, (char*)&buf, 0, 0);
			if (retval == SOCKET_ERROR)
				err_quit("recv()");
			cout << "똥" << endl;
		}
	}
}

MonsterPosForRecv* CSceneMgr::GetMonsterPos()
{
	return strMonsterPos;
}

PlayerInfo* CSceneMgr::GetPlayerPos()
{
	return strPlayerInfo;
}

int CSceneMgr::recvn(SOCKET s, char * buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
}

void CSceneMgr::SetKey(unsigned char _Key)
{
	charKey = _Key;
	//SendKey();
}

void CSceneMgr::SendKey(Vec3 _Position)
{
	int retval;
	int dataType = 0;

	retval = send(sock, (char*)&dataType, sizeof(dataType), 0);
	if (retval == SOCKET_ERROR)
		err_display("send()");

	//char buf[BUFSIZE];
	//cout << "보낸 인덱스 : " << strInitInfo->playerIndex << endl;
	tempPlayerInfo.playerIndex = strInitInfo->playerIndex;
	tempPlayerInfo.AniandKeyState = true;
	tempPlayerInfo.charKey = charKey;
	tempPlayerInfo.PlayerPos = _Position; 
	tempPlayerInfo.CameraDir = { 0 };
	tempPlayerInfo.type = 0;
	cout << "이친구를 보냄 : " << tempPlayerInfo.PlayerPos.fX << ", " << tempPlayerInfo.PlayerPos.fY << ", " << tempPlayerInfo.PlayerPos.fZ << endl;
	retval = send(sock, (char*)&tempPlayerInfo, sizeof(PlayerInfo), 0);
	if (retval == SOCKET_ERROR)
		err_display("send()");
	
	//스레드로 만들어서 타입으로 해보기

	

	//else
	//{
		/*char buf[BUFSIZE];
		retval = recv(sock, (char*)&buf, sizeof(PlayerInfo), 0);
		if (retval == SOCKET_ERROR)
			err_quit("recv()");*/
	//}

}

void CSceneMgr::RecvKey()
{
	/*int dataType = 0;

	retval = recv(sock, (char*)&dataType, sizeof(dataType), 0);
	if (retval == SOCKET_ERROR)
		err_quit("recv()");


	if (dataType == DataType::PLAYER)
	{
		retval = recv(sock, (char*)&tempInfo, sizeof(PlayerInfo), 0);
		if (retval == SOCKET_ERROR)
			err_quit("recv()");

		strPlayerInfo = &tempInfo;
		//cout << "temp값 : " << tempInfo.playerIndex << endl;
		cout << "인덱스 : " << strPlayerInfo->playerIndex << endl;
		cout << "받은값 : " << strPlayerInfo->PlayerPos.fX << ", " << strPlayerInfo->PlayerPos.fY << ", " << strPlayerInfo->PlayerPos.fZ << endl;
		//cout << "받은값 : " << strPlayerInfo->PlayerPos.fX << ", " << strPlayerInfo->PlayerPos.fY << ", " << strPlayerInfo->PlayerPos.fZ << endl;
		//strPlayerInfo.PlayerIndex += 1;
		//dynamic_cast<CCharacter*>(m_pCharacter)->SetCharRecvPosition(CSceneMgr::GetInitInfo(), CSceneMgr::GetPlayerPos());
	}

	else
	{
		char buf[BUFSIZE];
		retval = recv(sock, (char*)&buf, sizeof(PlayerInfo), 0);
		if (retval == SOCKET_ERROR)
		err_quit("recv()");
		cout << "플레이어 똥" << endl;
	}*/
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
