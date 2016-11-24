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
	static DWORD WINAPI ThreadFunc(LPVOID);	// ������ Ŭ���̾�Ʈ �ۼ����� ���� �������Լ�.
											// ���ڰ����δ� ������ Ŭ���̾�Ʈ ������ ����.
	static DWORD WINAPI MonsterPosUpdate(LPVOID);		//���� ��ġ�� �ǽð� ��������.

	
														
	void DeleteThread();
	void Init();
	void err_quit(char * msg);
	void err_display(char * msg);
	~CThreadManager();
private:
	SOCKET client_sock[2];							// �����ڷ� �޾ƿ��� �ΰ��� �������ڷ� �ʱ�ȭ��.
	HANDLE hThreadHandle[2];						// ���ϵ� ���� ��� ������ �ڵ鰪.
	HANDLE hMonPosUpdateHandle;						// MonsterPosUPdate ������ �ڵ鰪.

	/*static HANDLE hEventMonsterUpdate;
	static HANDLE hEventPlayerThread;*/
	//HANDLE hEventPlayer2Thread;
	

	static std::vector<PlayerInfo> playerVector;	// Player���� ���� �迭. Maxsize = 2.
	static std::vector<MonsterInfo> monsterVector;	// Monster���� ���� �迭. Maxsize = 10.
	static std::vector<BulletInfo> bulletVector;	// Bullet ���� ���� �迭. Ŭ��κ��� ���� �޼����� ������ 
													// Insert���ְ�, ������Ʈ����.
	static std::vector<ContainerInfo> conVector;	// Container���� ���� �迭. �浹üũ�� ���ȴ�.

	int retval;										// send, recv�� return value ����.
	int playerIndex;
	InitInfo initInform;							// 1�� player1, 2�� player2
	char buf[512];									// ���� ����.

	//static CRITICAL_SECTION csForPlayer;

};

