#include "ThreadManager.h"
#pragma comment(lib,"ws2_32")

std::vector<PlayerInfo> CThreadManager::playerVector;
std::vector<MonsterInfo> CThreadManager::monsterVector;
std::vector<BulletInfo> CThreadManager::bulletVector;
std::vector<ContainerInfo> CThreadManager::conVector;

HANDLE hEventMonsterUpdate;
HANDLE hEventPlayerThread;

CRITICAL_SECTION csForPlayer;
SOCKET global_client_sock[2];

struct MonsterUpdate
{
	SOCKET sock[2];
};

CThreadManager::CThreadManager() {};

CThreadManager::CThreadManager(SOCKET client_socket1, SOCKET client_socket2)
{
	client_sock[0] = client_socket1;
	client_sock[1] = client_socket2;
	playerIndex = 1;
	//Init();

	global_client_sock[0] = client_sock[0];
	global_client_sock[1] = client_sock[1];
	//Player1 Player2 ����
	//InitializeCriticalSection(&csForPlayer);

	//������ ����
	hThreadHandle[0] = CreateThread(
		NULL, 0, CThreadManager::ThreadFunc, (LPVOID)client_sock[0], CREATE_SUSPENDED, NULL);

	hThreadHandle[1] = CreateThread(
		NULL, 0, CThreadManager::ThreadFunc, (LPVOID)client_sock[1], CREATE_SUSPENDED, NULL);

	hMonPosUpdateHandle = CreateThread(
		NULL, 0, CThreadManager::MonsterPosUpdate, NULL, CREATE_SUSPENDED, NULL);

	//�̺�Ʈ ����
	hEventMonsterUpdate = CreateEvent(NULL, TRUE, FALSE, 0);
	if (hEventMonsterUpdate == nullptr)
		std::cout << "hEventMonsterUpdate ���� ����" << std::endl;

	hEventPlayerThread = CreateEvent(NULL, TRUE, TRUE, 0);
	if (hEventPlayerThread == nullptr)
		std::cout << "hEventPlayer1Thread ���� ����" << std::endl;

	/*hEventPlayer2Thread = CreateEvent(NULL,FALSE,TRUE,0);
	if (hEventPlayer2Thread == nullptr)
	std::cout << "hEventPlayer2Thread ���� ����" << std::endl;*/
}

void CThreadManager::Init()
{
	//�÷��̾� ��ġ�� �����ڿ��� �ʱ�ȭ.
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
	MonsterInfo a[10];

	a[0].MonsterPos = Vec3{ -1000,50,-1800 };
	a[1].MonsterPos = Vec3{ -1000,50,-1000 };
	a[2].MonsterPos = Vec3{ 1000,50,-1800 };
	a[3].MonsterPos = Vec3{ 1000,50,-1000 };
	a[4].MonsterPos = Vec3{ -500,50,-500 };
	a[5].MonsterPos = Vec3{ 0,50,0 };
	a[6].MonsterPos = Vec3{ 500,50,500 };
	a[7].MonsterPos = Vec3{ -1000,50,1000 };
	a[8].MonsterPos = Vec3{ 1000,50,1000 };
	a[9].MonsterPos = Vec3{ 0,50,1500 };

	for (int i = 0; i < 10; ++i)
	{
		a[i].type = DataType::MONSTER;
		a[i].hp = 3;
		monsterVector.push_back(a[i]);
	}
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
}
void CThreadManager::err_display(char * msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s \n", msg, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
	exit(1);
}
void CThreadManager::err_quit(char * msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}
DWORD WINAPI CThreadManager::MonsterPosUpdate(LPVOID params)
{
	std::cout << "monsterPosUpdate" << std::endl;

	float firstPosition[10];
	float monsterDirection[10];
	float moveRange = 300;
	int retval = 0;
	float leftTime = (1000 / 60);
	float nextTime = 0.0f;
	int nowTime = 0;
	MonsterPosForSend forSend;

	//���͵��� ���� �����ϰ� �ʱ�ȭ.
	for (int i = 0; i < 10; ++i)
	{
		firstPosition[i] = monsterVector[i].MonsterPos.x;

		monsterDirection[i] = rand() % 2 - 1;
		if (monsterDirection[i] == 0)
			monsterDirection[i] = 1;
	}
	int monsterType = 2;
	Sleep(500);

	while (true)
	{
		WaitForSingleObject(hEventPlayerThread, INFINITE);
		//std::cout << "MonsterTrheadWhileLoop" << std::endl;
		nowTime = std::clock();
		if (nowTime > nextTime)
		{
			for (int i = 0; i < 10; ++i)
			{
				if (monsterVector[i].MonsterPos.x < firstPosition[i] - moveRange)
					monsterDirection[i] *= -1;
				if (monsterVector[i].MonsterPos.x > firstPosition[i] + moveRange)
					monsterDirection[i] *= -1;
			}
			for (int i = 0; i < 10; ++i)
			{
				monsterVector[i].MonsterPos.x += (1 * monsterDirection[i]);
				forSend.monsters[i] = monsterVector[i];
			}
			//////////////////

			for (int i = 0; i < 2; ++i)
			{
				retval = send(global_client_sock[i], (char*)&monsterType, sizeof(int), 0);
				if (retval == SOCKET_ERROR)
				{
					std::cout << "send����1" << std::endl;
				}
			}

			for (int i = 0; i < 2; ++i)
			{
				retval = send(global_client_sock[i], (char*)&forSend, sizeof(MonsterPosForSend), 0);
				if (retval == SOCKET_ERROR)
				{
					std::cout << "send����2" << std::endl;
				}
			}

			nextTime = std::clock() + leftTime;
			SetEvent(hEventMonsterUpdate);
		}

	}
}
DWORD WINAPI CThreadManager::ThreadFunc(LPVOID param)
{
	std::cout << "������ ����!" << std::endl;
	SOCKET client_sock = (SOCKET)param;
	SOCKADDR_IN clientaddr;
	//getpeername(client_sock,(SOCKADDR*)&clientaddr,&addrlen);

	COperator calculate = { &playerVector, &monsterVector, &bulletVector };

	int retval;         //return value
	char buf[BUFSIZE];
	int dataType = 0;
	PlayerInfo a;

	while (true)            //�� �Լ������� send,recv �۾��� �̷����.
	{
		//std::cout << "ThreadFuncWhileLoop" << std::endl;
		std::cout << "recv�����.." << std::endl;
		retval = recv(client_sock, (char*)&dataType, sizeof(int), 0);
		if (retval == SOCKET_ERROR)
		{
			std::cout << "���ú� ����1" << std::endl;
		}
		std::cout << "recv ��.." << std::endl;
		if (DataType::PLAYER == dataType)
		{

			retval = recv(client_sock, (char*)&a, sizeof(PlayerInfo), 0);
			if (retval == SOCKET_ERROR)
			{
				std::cout << "���ú� ����2" << std::endl;
			}
			//EnterCriticalSection(&csForPlayer);

			calculate.PlayerPosUpdate(a, &playerVector);

			//LeaveCriticalSection(&csForPlayer);
			WaitForSingleObject(hEventMonsterUpdate, INFINITE);
			for (int i = 0; i < 2; ++i)
			{
				retval = send(global_client_sock[i], (char*)&dataType, sizeof(int), 0);
				if (retval == SOCKET_ERROR)
				{
					std::cout << "���� ����1" << std::endl;
				}
			}
			for (int i = 0; i < 2; ++i)
			{
				retval = send(global_client_sock[i], (char*)&a, sizeof(PlayerInfo), 0);
				if (retval == SOCKET_ERROR)
				{
					std::cout << "���� ����2" << std::endl;
				}
			}
			SetEvent(hEventPlayerThread);
		}

		//�����˻繮 �ʿ�
		//calculate.Update();

	}
	return 0;
}

void CThreadManager::Update()
{
	Init();

	std::cout << "�ʱⰪ ����" << std::endl;
	for (int i = 0; i<2; ++i)
	{
		retval = send(client_sock[i], (char*)&initInform, sizeof(InitInfo), 0);         //���� �ʱⰪ ����.
		if (retval == SOCKET_ERROR)
		{
			err_display("send()");
		}
		initInform.playerIndex += 1;
	}
	std::cout << "�ʱⰪ ���� �Ϸ�." << std::endl;


	std::cout << "�غ�Ϸ� �޼��� ����" << std::endl;         // ������ ù��° Ŭ�� �ι�° Ŭ�� ������ �޾ƾ���
	for (int i = 0; i<2; ++i)                           // ���� ���� �ʿ�.
	{
		retval = recv(client_sock[i], buf, sizeof(buf), 0);         //�غ�Ϸ� �޼��� ����. ���Ż����� �����ؾߵ�.
		if (retval == SOCKET_ERROR)
		{
			err_display("recv()");
		}
	}
	std::cout << "�غ�Ϸ� �޼��� ���� �Ϸ�" << std::endl;

	std::cout << "����ȯ �޼��� �۽�" << std::endl;

	SceneInfo changeGameScene;         //8byte ����.   
	changeGameScene.type = DataType::SCENE;
	changeGameScene.SceneState = SceneList::INGAME;

	for (int i = 0; i < 2; ++i)            //send - ���Ӿ����� �Ѿ��� �޼��� ����
	{
		retval = send(client_sock[i], (char*)&changeGameScene, sizeof(SceneInfo), 0);
		if (retval == SOCKET_ERROR)
		{
			err_display("send()");
		}
	}
	std::cout << "����ȯ �޼��� ������ �Ϸ�" << std::endl;

	//ResumeThread ���ֱ����� ���� �ʱⰪ�� �������ְ� �����غ�Ϸ� �Ǹ� ResumeThread ���ش�.
	ResumeThread(hThreadHandle[0]);
	ResumeThread(hThreadHandle[1]);

	ResumeThread(hMonPosUpdateHandle);

	std::cout << "������ 3�� ����?" << std::endl;
	WaitForMultipleObjects(2, hThreadHandle, TRUE, INFINITE);
	WaitForSingleObject(hMonPosUpdateHandle, INFINITE);
	std::cout << "������ 3�� ����!" << std::endl;
}

CThreadManager::~CThreadManager()
{
	DeleteCriticalSection(&csForPlayer);
}