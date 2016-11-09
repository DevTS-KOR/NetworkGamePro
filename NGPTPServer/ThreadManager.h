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
	static DWORD WINAPI ThreadFunc(LPVOID);	// ������ Ŭ���̾�Ʈ �ۼ����� ���� �������Լ�.
											// ���ڰ����δ� ������ Ŭ���̾�Ʈ ������ ����.
	void DeleteThread();
	void AddBullet();
	void Init();
	void err_quit(char * msg);
	void err_display(char * msg);

	~CThreadManager();
private:
	SOCKET client_sock[2];							// �����ڷ� �޾ƿ��� �ΰ��� �������ڷ� �ʱ�ȭ��.
	HANDLE hThreadHandle[2];						// �������� �ڵ鰪.
	static std::vector<PlayerInfo> playerVector;	// Player���� ���� �迭. Maxsize = 2.
	static std::vector<MonsterInfo> monsterVector;	// Monster���� ���� �迭. Maxsize = 10.
	static std::vector<BulletInfo> bulletVector;	// Bullet ���� ���� �迭. Ŭ��κ��� ���� �޼����� ������ 
													// Insert���ְ�, ������Ʈ����.
	static std::vector<ContainerInfo> conVector;	// Container���� ���� �迭. �浹üũ�� ���ȴ�.

	int retval;										// send, recv�� return value ����.
	int playerIndex;
	InitInfo initInform1, initInform2;				// 1�� player1, 2�� player2
};

