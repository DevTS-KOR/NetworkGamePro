#pragma once
#include <chrono>
#include <ctime>
#include "Operator.h"
class CThreadManager
{
public:
	CThreadManager();
	CThreadManager(SOCKET, SOCKET);
	void Update();
	static DWORD WINAPI ThreadFunc(LPVOID);	// 각각의 클라이언트 송수신을 위한 스레드함수.
											// 인자값으로는 각각의 클라이언트 소켓을 받음.
	static DWORD WINAPI MonsterPosUpdate(LPVOID);		//몬스터 위치값 실시간 움직여줌.

	
														
	void DeleteThread();
	void Init();
	void err_quit(char * msg);
	void err_display(char * msg);
	~CThreadManager();
private:
	SOCKET client_sock[2];							// 생성자로 받아오는 두개의 소켓인자로 초기화됨.
	HANDLE hThreadHandle[2];						// 소켓들 간의 통신 스레드 핸들값.
	HANDLE hMonPosUpdateHandle;						// MonsterPosUPdate 스레드 핸들값.

	/*static HANDLE hEventMonsterUpdate;
	static HANDLE hEventPlayerThread;*/
	//HANDLE hEventPlayer2Thread;
	

	static std::vector<PlayerInfo> playerVector;	// Player정보 관리 배열. Maxsize = 2.
	static std::vector<MonsterInfo> monsterVector;	// Monster정보 관리 배열. Maxsize = 10.
	static std::vector<BulletInfo> bulletVector;	// Bullet 정보 관리 배열. 클라로부터 생성 메세지를 받으면 
													// Insert해주고, 업데이트해줌.
	static std::vector<ContainerInfo> conVector;	// Container정보 관리 배열. 충돌체크에 사용된다.

	int retval;										// send, recv에 return value 값들.
	int playerIndex;
	InitInfo initInform;							// 1은 player1, 2는 player2
	char buf[512];									// 버퍼 변수.

	//static CRITICAL_SECTION csForPlayer;

};

