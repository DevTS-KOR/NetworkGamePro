#include <WinSock2.h>
#include <iostream>
#include <vector>
#include <Windows.h>
#include <ctime>
#include "Protocol.h"
#pragma comment(lib,"ws2_32")
using namespace std;
#define SERVERPORT 9595
#define BUFSIZE 512
//-----------����������----------//
SOCKET global_client_sock[2];					// Ŭ���̾�Ʈ ���� ����
vector<PlayerInfo> playerVector;
vector<MonsterInfo> monsterVector;
vector<BulletInfo> bulletVector;
vector<ContainerInfo> conVector;
SceneInfo changeGameScene;				//8byte ����.  
InitInfo initInform;
HANDLE hEventMonsterUpdate;				//�̺�Ʈ �ڵ�
HANDLE hEventPlayerThread1;				//�̺�Ʈ �ڵ�.
HANDLE hEventPlayerThread2;

DataPacket packet;

double leftTime = (100 / 6);

static int NUM= 0;

//-----------�Լ� ����----------//
DWORD WINAPI ThreadFunc1(LPVOID);	
DWORD WINAPI ThreadFunc2(LPVOID);
void PlayerPosUpdate(PlayerInfo*);
void Init();
void MonsterUpdate();
bool CollisionBulletWithMonster(BulletInfo&, MonsterInfo&);								// �Ѿ��ϰ� ���� �浹�Լ�
bool CollisionBulletWithMap(BulletInfo&);												// ����ü�ϰ� �Ѿ�
bool CollisionBulletWithObstacle(BulletInfo&bullet, ContainerInfo& container);			// �Ѿ��ϰ� ��ֹ� �浹�Լ�
bool CollisionObstacleWithPlayer(PlayerInfo&, ContainerInfo&);							// ��ֹ��� �÷��̾� �浹�Լ�

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKADDR_IN server_addr;	// ���� ���� �ּ� ����ü
	SOCKADDR_IN client_addr;	// Ŭ�� ���� �ּ� ����ü
	SOCKET listen_sock;			// Listen Socket ����
	int retval;					// return Value �� �޴� ����
	int ClientNum = 0;			// Ŭ�� � �����ߴ���
	int addrlen;				// �ּ� ����
	int playerIndex;
	HANDLE hThreadHandle1;
	HANDLE hThreadHandle2;
	
	char buf[BUFSIZE];	
	
	//���� �ʱ�ȭ �۾�
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//Socket()
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET)
		err_quit("listen_sock()");

	//Bind()
	ZeroMemory(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR*)&server_addr, sizeof(server_addr));
	if (retval == SOCKET_ERROR)
		err_quit("Bind()");

	//Listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
		err_quit("Listen()");    

	while (true)
	{
		//Accept
		addrlen = sizeof(client_addr);
		global_client_sock[ClientNum] = accept(listen_sock, (SOCKADDR*)&client_addr, &addrlen);
		if (global_client_sock[ClientNum] == INVALID_SOCKET)
			err_quit("client_socket");
		printf("%d ��° Ŭ������ : IP : %s, ��Ʈ��ȣ : %d \n",ClientNum+1, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		if (ClientNum < 2)
			ClientNum++;
		if (ClientNum == 2)
		{
			ClientNum++;
			break;
		}
	}

	//������ ����.
	hThreadHandle1 = CreateThread(
		NULL, 0, ThreadFunc1, (LPVOID)global_client_sock[0], CREATE_SUSPENDED, NULL);

	hThreadHandle2 = CreateThread(
		NULL, 0, ThreadFunc2, (LPVOID)global_client_sock[1], CREATE_SUSPENDED, NULL);

	//�̺�Ʈ ����
	hEventMonsterUpdate = CreateEvent(NULL, FALSE, FALSE, 0);
	if (hEventMonsterUpdate == nullptr)
		cout << "hEventMonsterUpdate ���� ����" << endl;
	hEventPlayerThread1 = CreateEvent(NULL, FALSE, FALSE, 0);
	if (hEventPlayerThread1 == nullptr)
		cout << "hEventPlayer1Thread ���� ����" << endl;
	hEventPlayerThread2 = CreateEvent(NULL, FALSE, TRUE, 0);
	if (hEventPlayerThread2 == nullptr)
		cout << "hEventPlayer1Thread ���� ����" << endl;

	Init();			//�����͵� �ʱ�ȭ

	cout << "�ʱⰪ ����" << std::endl;
	for (int i = 0; i<2; ++i)
	{
		retval = send(global_client_sock[i], (char*)&initInform, sizeof(InitInfo), 0);         //���� �ʱⰪ ����.
		if (retval == SOCKET_ERROR)
		{
			err_display("send()");
		}
		initInform.playerIndex += 1;
	}
	cout << "�ʱⰪ ���� �Ϸ�." << std::endl;

	std::cout << "�غ�Ϸ� �޼��� ����" << std::endl;         // ������ ù��° Ŭ�� �ι�° Ŭ�� ������ �޾ƾ���
	for (int i = 0; i<2; ++i)                           // ���� ���� �ʿ�.
	{
		retval = recv(global_client_sock[i], buf, sizeof(buf), 0);         //�غ�Ϸ� �޼��� ����. ���Ż����� �����ؾߵ�.
		if (retval == SOCKET_ERROR)
		{
			err_display("recv()");
		}
	}
	std::cout << "�غ�Ϸ� �޼��� ���� �Ϸ�" << std::endl;

	std::cout << "����ȯ �޼��� �۽�" << std::endl;
 
	changeGameScene.type = DataType::SCENE;
	changeGameScene.SceneState = SceneList::INGAME;

	for (int i = 0; i < 2; ++i)            //send - ���Ӿ����� �Ѿ��� �޼��� ����
	{
		retval = send(global_client_sock[i], (char*)&changeGameScene, sizeof(SceneInfo), 0);
		if (retval == SOCKET_ERROR)
		{
			err_display("send()");
		}
	}
	std::cout << "����ȯ �޼��� ������ �Ϸ�" << std::endl;

	//OK

	//ResumeThread ���ֱ����� ���� �ʱⰪ�� �������ְ� �����غ�Ϸ� �Ǹ� ResumeThread ���ش�.
	ResumeThread(hThreadHandle1);
	ResumeThread(hThreadHandle2);

	//MontserPosUpdate()

	MonsterUpdate();

	cout << "������ 2�� ����?" << endl;
	WaitForSingleObject(hThreadHandle1, INFINITE);
	WaitForSingleObject(hThreadHandle2, INFINITE);
	cout << "������ 2�� ����!" << endl;

	CloseHandle(hEventMonsterUpdate);
	CloseHandle(hEventPlayerThread1);
	CloseHandle(hEventPlayerThread2);

	closesocket(listen_sock);
	closesocket(global_client_sock[0]);
	closesocket(global_client_sock[1]);

	return 0;
}
void Init()
{
	playerVector.reserve(2);
	playerVector.push_back(PlayerInfo{ DataType::PLAYER,1,Vec3{ -1500,50,1900 },Vec3{ 0,0,0 },false });
	playerVector.push_back(PlayerInfo{ DataType::PLAYER,2,Vec3{ 1500,50,1900 },Vec3{ 0,0,0 },false });

	// �����̳� ��ġ�� �� ������ �ʱ�ȭ -> �浹üũ�� ���ɰ�/
	conVector.reserve(4);
	conVector.push_back(ContainerInfo{ Vec3{ 0,300,1000 } });
	conVector.push_back(ContainerInfo{ Vec3{ 1500,300,0 } });
	conVector.push_back(ContainerInfo{ Vec3{ 0,300,-1000 } });
	conVector.push_back(ContainerInfo{ Vec3{ -1500,300,0 } });

	//Vec3  a{ 1,2,3 };
	int hp = 3;
	// ���͵� ��ġ�� �ʱ�ȭ
	monsterVector.reserve(10);
	monsterVector.push_back(MonsterInfo{ DataType::MONSTER,Vec3{ -1000,50,-1800 } ,3,0 });
	monsterVector.push_back(MonsterInfo{ DataType::MONSTER,Vec3{ -1000,50,-1000 } ,3,1 });
	monsterVector.push_back(MonsterInfo{ DataType::MONSTER,Vec3{ 1000,50,-1800 } ,3,2 });
	monsterVector.push_back(MonsterInfo{ DataType::MONSTER,Vec3{ 1000,50,-1000 } ,3,3 });
	monsterVector.push_back(MonsterInfo{ DataType::MONSTER,Vec3{ -500,50,-500 } ,3,4 });
	monsterVector.push_back(MonsterInfo{ DataType::MONSTER,Vec3{ 0,50,0 } ,3,5 });
	monsterVector.push_back(MonsterInfo{ DataType::MONSTER,Vec3{ 500,50,500 } ,3,6 });
	monsterVector.push_back(MonsterInfo{ DataType::MONSTER,Vec3{ -1000,50,1000 } ,3,7 });
	monsterVector.push_back(MonsterInfo{ DataType::MONSTER,Vec3{ 1000,50,1000 } ,3,8 });
	monsterVector.push_back(MonsterInfo{ DataType::MONSTER,Vec3{ 0,50,1500 } ,3,9 });

	//��Ŭ���̾�Ʈ�� ���� �ʱⰪ�鿡 �ʱ�ȭ.
	// Player1,2

	initInform.Player1Pos = Vec3{ -1500, 50, 1900 };
	initInform.Player2Pos = Vec3{ 1500, 50, 1900 };

	//Monsters
	initInform.MonsterPos[0] = Vec3{ -1000,50,-1800 };
	initInform.MonsterPos[1] = Vec3{ -1000,50,-1000 };
	initInform.MonsterPos[2] = Vec3{ 1000,50,-1800 };
	initInform.MonsterPos[3] = Vec3{ 1000,50,-1000 };
	initInform.MonsterPos[4] = Vec3{ -500,50,-500 };
	initInform.MonsterPos[5] = Vec3{ 0,50,0 };
	initInform.MonsterPos[6] = Vec3{ 500,50,500 };
	initInform.MonsterPos[7] = Vec3{ -1000,50,1000 };
	initInform.MonsterPos[8] = Vec3{ 1000,50,1000 };
	initInform.MonsterPos[9] = Vec3{ 0,50,1500 };

	initInform.playerIndex = 1;

	//Send,Recv���� ��Ŷ �ʱ�ȭ
	for (int i = 0; i < 10; ++i)
	{
		packet.monsters[i] = monsterVector[i];
	}
	packet.player1 = playerVector[0];
	packet.player2 = playerVector[1];
	

}
void MonsterUpdate()
{
	std::cout << "monsterPosUpdate in Main Function" << std::endl;

	float firstPosition[10];
	float monsterDirection[10];
	float moveRange = 300;
	int retval = 0;

	char buf1[10];
	char buf2[BUFSIZE];

	//���͵��� ���� �����ϰ� �ʱ�ȭ.
	for (int i = 0; i < 10; ++i)
	{
		firstPosition[i] = monsterVector[i].MonsterPos.x;

		monsterDirection[i] = rand() % 2 - 1;
		if (monsterDirection[i] == 0)
			monsterDirection[i] = 1;
	}
	int monsterType = DataType::MONSTER;
	int bulletType = DataType::BULLET;
	int packetType = DataType::PACKET;
	double nextTime = 0.0f;
	double nowTime = clock();


	while (true)
	{
		WaitForSingleObject(hEventPlayerThread2, INFINITE);
		nowTime = std::clock();
		if (nowTime > nextTime)
		{
			//���� ��ġ ������Ʈ
			for (int i = 0; i < 10; ++i)
			{
				if (monsterVector[i].MonsterPos.x < firstPosition[i] - moveRange)
					monsterDirection[i] *= -1;
				if (monsterVector[i].MonsterPos.x > firstPosition[i] + moveRange)
					monsterDirection[i] *= -1;
			}
			for (int i = 0; i < 10; ++i)
			{
				monsterVector[i].MonsterPos.x += (5 * monsterDirection[i]);
				packet.monsters[i] = monsterVector[i];
			}

			//�Ѿ� ��ġ ������Ʈ.
			//if (bulletVector.size() != 0)
			//{
			//	for (int i = 0; i < bulletVector.size(); ++i)
			//	{
			//	}
			//}

			//�����͸� ��� ������.
			for (int i = 0; i < 2; ++i)
			{
				retval = send(global_client_sock[i], (char*)&packetType, sizeof(int), 0);
				if (retval == SOCKET_ERROR)
				{
					err_display("send1()");
				}
			}

			for (int i = 0; i < 2; ++i)
			{
				retval = send(global_client_sock[i], (char*)&packet, sizeof(DataPacket), 0);
				if (retval == SOCKET_ERROR)
				{
					err_display("send1()");
				}
			}

			//�Ѿ� ����
		/*	if (bulletVector.size()!=0)
			{
				for (int i = 0; i < 2; ++i)
				{
					retval = send(global_client_sock[i], (char*)&bulletType, sizeof(int), 0);
					if (retval == SOCKET_ERROR)
					{
						err_display("send1 in Bulet()");
					}
				}

				for (int i = 0; i < bulletVector.size(); ++i)
				{
					retval = send(global_client_sock[i], (char*)&bulletVector[i], sizeof(MonsterPosForSend), 0);
					if (retval == SOCKET_ERROR)
					{
						err_display("send1 in bullet()");
					}
				}
			}*/

			nextTime = clock() + leftTime;

		}
		SetEvent(hEventMonsterUpdate);
	}
}

DWORD WINAPI ThreadFunc1(LPVOID param)
{
	cout << "������ ����!" << endl;
	SOCKET client_sock = (SOCKET)param;
	int retval;         //return value
	char buf[BUFSIZE];
	int dataType = 0;
	PlayerInfo playerInfoForRS;		//���帮�ú� ���� ����ü
	BulletInfo bulletInfoForRS;		//�Ѿ� ���帮�ú� ���� ����ü;
	int playerIndex;

	double nextTime = 0.0f;
	double nowTime = clock();

	while (true)            //�� �Լ������� send,recv �۾��� �̷����.
	{
		WaitForSingleObject(hEventMonsterUpdate, INFINITE);
		nowTime = std::clock();
		if (nowTime > nextTime)
		{
			printf("THread Func1 recv waiting.. \n");

			retval = recv(client_sock, (char*)&dataType, sizeof(int), 0);
			if (retval == SOCKET_ERROR)
				err_display("recv");

			printf("THread Func1 recv Complete.. \n");
			printf("Thread FUnc1 Come Data : %d \n", dataType);

		/*
			if (DataType::BULLET)
			{
				retval = recv(client_sock, (char*)&bulletInfoForRS, sizeof(BulletInfo), 0);
				if (retval == SOCKET_ERROR)
				{
					err_display("recv");
				}

				bulletVector.push_back(bulletInfoForRS);

			}*/

			if (DataType::PLAYER == dataType)
			{
				printf("ThreadFunc1 PlayerType Call \n");
				retval = recv(client_sock, (char*)&playerInfoForRS, sizeof(PlayerInfo), 0);
				if (retval == SOCKET_ERROR)
				{
					err_display("recv");
				}
				playerIndex = playerInfoForRS.playerIndex;

				playerVector[playerIndex - 1].PlayerPos = playerInfoForRS.PlayerPos;
				//����̿� �浹üũ ��������
				packet.player1 = playerInfoForRS;

				printf("playerINfoFOrRS IN threadFUnc1 x : %f y :  %f  z :%f  \n",
					playerInfoForRS.PlayerPos.x,
					playerInfoForRS.PlayerPos.y,
					playerInfoForRS.PlayerPos.z);
			}
			printf("ThreadFunc1 Call Set event \n");
			nextTime = clock() + leftTime;
		}
		SetEvent(hEventPlayerThread1);
	}
	return 0;
}
DWORD WINAPI ThreadFunc2(LPVOID param)
{
	cout << "������ ����!" << endl;
	SOCKET client_sock = (SOCKET)param;
	int retval;         //return value
	char buf[BUFSIZE];
	int dataType = 0;
	PlayerInfo playerInfoForRS;		//���帮�ú� ���� ����ü
	int playerIndex;

	double nextTime = 0.0f;
	double nowTime = clock();

	while (true)            //�� �Լ������� send,recv �۾��� �̷����.
	{
		WaitForSingleObject(hEventPlayerThread1, INFINITE);
		nowTime = std::clock();
		if (nowTime > nextTime)
		{
			printf("THread Func2 recv waiting.. \n");
			retval = recv(client_sock, (char*)&dataType, sizeof(int), 0);
			if (retval == SOCKET_ERROR)
				err_display("recv");

			printf("THread Func2 recv Complete.. \n");
			printf("Thread FUnc2 Come Data : %d \n", dataType);

			if (DataType::PLAYER == dataType)
			{
				printf("ThreadFunc2 PlayerType Call \n");
				retval = recv(client_sock, (char*)&playerInfoForRS, sizeof(PlayerInfo), 0);
				if (retval == SOCKET_ERROR)
				{
					err_display("recv");
				}

				playerIndex = playerInfoForRS.playerIndex;

				playerVector[playerIndex - 1].PlayerPos = playerInfoForRS.PlayerPos;

				packet.player2 = playerInfoForRS;

				printf("playerINfoFOrRS In THreadFUnc2 x : %f y :  %f  z :%f  \n",
					playerInfoForRS.PlayerPos.x,
					playerInfoForRS.PlayerPos.y,
					playerInfoForRS.PlayerPos.z);
			}
			printf("ThreadFunc2 Call Set event \n"); 
			nextTime = clock() + leftTime;
		}
		SetEvent(hEventPlayerThread2);
	}
	return 0;
}
void PlayerPosUpdate(PlayerInfo* param)
{
	PlayerInfo a = *param;
	std::cout << "PlayerPosUpdateȣ��" << std::endl;
	std::cout <<"a.playerINDex :: \n"<< a.playerIndex << std::endl;

	if (a.playerIndex == 1)  
	{
		if (a.charKey == 'w')
		{
			std::cout << "p1 wŰ��" << std::endl;
			playerVector[0].PlayerPos.z -= 10;
		}
		if (a.charKey == 's')
		{
			std::cout << "p1 sŰ��" << std::endl;
			playerVector[0].PlayerPos.z += 10;
		}
		if (a.charKey == 'a')
		{
			std::cout << "p1 aŰ��" << std::endl;
			playerVector[0].PlayerPos.x -= 10;
		}
		if (a.charKey == 'd')
		{
			std::cout << "p1 dŰ��" << std::endl;
			playerVector[0].PlayerPos.x += 10;
		}
	}
	else if (a.playerIndex == 2)
	{
		if (a.charKey == 'w')
		{
			std::cout << "p2 wŰ��" << std::endl;
			playerVector[1].PlayerPos.z -= 10;
		}
		if (a.charKey == 's')
		{
			std::cout << "p2 sŰ��" << std::endl;
			playerVector[1].PlayerPos.z += 10;
		}
		if (a.charKey == 'a')
		{
			std::cout << "p2 aŰ��" << std::endl;
			playerVector[1].PlayerPos.x -= 10;
		}
		if (a.charKey == 'd')
		{
			std::cout << "p2 dŰ��" << std::endl;
			playerVector[1].PlayerPos.x += 10;
		}
	}
}
bool CollisionBulletWithMonster(BulletInfo & bullet, MonsterInfo& monster)
{
	return(
		bullet.BulletPos.x + 1 > monster.MonsterPos.x - 30 &&
		bullet.BulletPos.x - 1 < monster.MonsterPos.x + 30 &&
		bullet.BulletPos.y + 1 > monster.MonsterPos.y - 55 &&
		bullet.BulletPos.y - 1 < monster.MonsterPos.y + 55 &&
		bullet.BulletPos.z + 1 > monster.MonsterPos.z - 15 &&
		bullet.BulletPos.z - 1 < monster.MonsterPos.z + 15
		);
}
bool CollisionBulletWithObstacle(BulletInfo&bullet, ContainerInfo& container)
{
	return(
		bullet.BulletPos.x + 1 > container.position.x - 128 &&
		bullet.BulletPos.x - 1 < container.position.x + 128 &&
		bullet.BulletPos.y + 1 > container.position.y - 128 &&
		bullet.BulletPos.y - 1 < container.position.y + 128 &&
		bullet.BulletPos.z + 1 > container.position.z - 256 &&
		bullet.BulletPos.z - 1 < container.position.z + 256
		);
}
bool CollisionBulletWithMap(BulletInfo& bullet)
{
	if (bullet.BulletPos.x + 1 > 2000)
		return true;
	if (bullet.BulletPos.x - 1 < -2000)
		return true;
	if (bullet.BulletPos.y + 1 > 2000)
		return true;
	if (bullet.BulletPos.y - 1 < -2000)
		return true;

	return false;
}
bool CollisionObstacleWithPlayer(PlayerInfo&player, ContainerInfo& container)
{
	return(
		player.PlayerPos.x + 30 > container.position.x - 128 &&
		player.PlayerPos.x - 30 < container.position.x + 128 &&
		player.PlayerPos.z +  15> container.position.z - 256 &&
		player.PlayerPos.z - 15 < container.position.z + 256
		);

	//Ʈ��� ���������� ��������.
}