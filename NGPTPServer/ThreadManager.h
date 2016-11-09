#pragma once
#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <iostream>
#include <vector>
#include "Protocol.h"
class CThreadManager
{
public:
	CThreadManager();
	CThreadManager(SOCKET, SOCKET);
	void Update();
	static DWORD WINAPI ThreadFunc(LPVOID);	// 각각의 클라이언트 송수신을 위한 스레드함수.
											// 인자값으로는 각각의 클라이언트 소켓을 받음.
	void DeleteThread();
	void AddBullet();
	void Init();
	void err_quit(char * msg);
	void err_display(char * msg);

	~CThreadManager();
private:
	SOCKET client_sock[2];							// 생성자로 받아오는 두개의 소켓인자로 초기화됨.
	HANDLE hThreadHandle[2];						// 스레드의 핸들값.
	static std::vector<PlayerInfo> playerVector;	// Player정보 관리 배열. Maxsize = 2.
	static std::vector<MonsterInfo> monsterVector;	// Monster정보 관리 배열. Maxsize = 10.
	static std::vector<BulletInfo> bulletVector;	// Bullet 정보 관리 배열. 클라로부터 생성 메세지를 받으면 
													// Insert해주고, 업데이트해줌.
	static std::vector<ContainerInfo> conVector;	// Container정보 관리 배열. 충돌체크에 사용된다.

	int retval;										// send, recv에 return value 값들.
	int playerIndex;
	InitInfo initInform1, initInform2;				// 1은 player1, 2는 player2
};

