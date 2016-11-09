#include "ThreadManager.h"
#pragma comment(lib,"ws2_32")

std::vector<PlayerInfo> CThreadManager::playerVector;
CThreadManager::CThreadManager(){}

CThreadManager::CThreadManager(SOCKET client_socket1,SOCKET client_socket2)
{
	client_sock[0] = client_socket1;
	client_sock[1] = client_socket2;

	playerIndex = 1;
	Init();

	//Player1 Player2 ����

	hThreadHandle[0] = CreateThread(
		NULL, 0, CThreadManager::ThreadFunc, (LPVOID)client_sock[0], CREATE_SUSPENDED, NULL);
	hThreadHandle[1] = CreateThread(
		NULL, 0, CThreadManager::ThreadFunc, (LPVOID)client_sock[1], CREATE_SUSPENDED, NULL);

	/*hThreadHandle[0] = CreateThread(
		NULL, 0, CThreadManager::ThreadFunc, (LPVOID)0, CREATE_SUSPENDED, NULL);
	hThreadHandle[1] = CreateThread(
		NULL, 0, CThreadManager::ThreadFunc, (LPVOID)1, CREATE_SUSPENDED, NULL);*/
}

void CThreadManager::Init()
{
	//�÷��̾� ��ġ�� �����ڿ��� �ʱ�ȭ.
	playerVector.push_back(PlayerInfo{ DataType::PLAYER,Vec3{ 1500,100,1900 },Vec3{ -1500,100,1900 },false });
	playerVector.push_back(PlayerInfo{ DataType::PLAYER,Vec3{ 1500,100,1900 },Vec3{ -1500,100,1900 },false });

	// �����̳� ��ġ�� �� ������ �ʱ�ȭ -> �浹üũ�� ���ɰ�/
	conVector.push_back(ContainerInfo{ 0,300,1000 });
	conVector.push_back(ContainerInfo{ 1500,300,0 });
	conVector.push_back(ContainerInfo{ 0,300,-1000 });
	conVector.push_back(ContainerInfo{ -1500,300,0 });

	// ���͵� ��ġ�� �ʱ�ȭ
	monsterVector.push_back(MonsterInfo{ DataType::MONSTER,Vec3{-1000,100,-1800},3 });
	monsterVector.push_back(MonsterInfo{ DataType::MONSTER,Vec3{ -1000,100,-1000 },3 });
	monsterVector.push_back(MonsterInfo{ DataType::MONSTER,Vec3{ 1000,100,-1800 },3 });
	monsterVector.push_back(MonsterInfo{ DataType::MONSTER,Vec3{ 1000,100,-1000 },3 });
	monsterVector.push_back(MonsterInfo{ DataType::MONSTER,Vec3{ -500,100,-500 },3 });
	monsterVector.push_back(MonsterInfo{ DataType::MONSTER,Vec3{ 0,100,0 },3 });
	monsterVector.push_back(MonsterInfo{ DataType::MONSTER,Vec3{ 500,100,500 },3 });
	monsterVector.push_back(MonsterInfo{ DataType::MONSTER,Vec3{ -1000,100,1000 },3 });
	monsterVector.push_back(MonsterInfo{ DataType::MONSTER,Vec3{ 1000,100,1000 },3 });
	monsterVector.push_back(MonsterInfo{ DataType::MONSTER,Vec3{ 0,100,1500 },3 });

	//��Ŭ���̾�Ʈ�� ���� �ʱⰪ�鿡 �ʱ�ȭ.
	// Player1,2
	initInform1.playerIndex = 1;
	initInform2.playerIndex = 2;

	initInform1.Player1Pos = Vec3{ -1500, 100, 1900 };
	initInform1.Player2Pos = Vec3{ 1500, 100, 1900 };

	initInform2.Player1Pos = Vec3{ -1500, 100, 1900 };
	initInform2.Player2Pos = Vec3{ 1500, 100, 1900 };

	//Monsters
	initInform1.MonsterPos[0] = Vec3{ -1000,100,-1800 };
	initInform1.MonsterPos[1] = Vec3{ -1000,100,-1000 };
	initInform1.MonsterPos[2] = Vec3{ 1000,100,-1800 };
	initInform1.MonsterPos[3] = Vec3{ 1000,100,-1000 };
	initInform1.MonsterPos[4] = Vec3{ -500,100,-500 };
	initInform1.MonsterPos[5] = Vec3{ 0,100,0 };
	initInform1.MonsterPos[6] = Vec3{ 500,100,500 };
	initInform1.MonsterPos[7] = Vec3{ -1000,100,1000 };
	initInform1.MonsterPos[8] = Vec3{ 1000,100,1000 };
	initInform1.MonsterPos[9] = Vec3{ 0,100,1500 };

	initInform2.MonsterPos[0] = Vec3{ -1000,100,-1800 };
	initInform2.MonsterPos[1] = Vec3{ -1000,100,-1000 };
	initInform2.MonsterPos[2] = Vec3{ 1000,100,-1800 };
	initInform2.MonsterPos[3] = Vec3{ 1000,100,-1000 };
	initInform2.MonsterPos[4] = Vec3{ -500,100,-500 };
	initInform2.MonsterPos[5] = Vec3{ 0,100,0 };
	initInform2.MonsterPos[6] = Vec3{ 500,100,500 };
	initInform2.MonsterPos[7] = Vec3{ -1000,100,1000 };
	initInform2.MonsterPos[8] = Vec3{ 1000,100,1000 };
	initInform2.MonsterPos[9] = Vec3{ 0,100,1500 };


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

DWORD WINAPI CThreadManager::ThreadFunc(LPVOID param)
{
	SOCKET client_sock = (SOCKET)param;
	//int a = (int)param;
	SOCKADDR_IN clientaddr;
	int addrlen;
	//getpeername(client_sock,(SOCKADDR*)&clientaddr,&addrlen);

	while (true)				//�� �Լ������� send,recv �۾��� �̷����.
	{
		//recv
		//Operate
		//send
		//std::cout << playerVector[a].PlayerPos.x << std::endl;
		std::cout << "hello" << std::endl;
	}
}

void CThreadManager::Update()
{
	char buf[10] = "�ʱⰪ";
	int len;
	len = strlen(buf);
	if (buf[len - 1] == '\n')
		buf[len - 1] = '\0';

	for(int i =0 ;i<2;++i)
	{
		retval = send(client_sock[i], buf, sizeof(len), 0);			//���� �ʱⰪ ����.
		if (retval == SOCKET_ERROR)
		{
			err_display("send()");
		}
	}
	std::cout << "����" << std::endl;
	for (int i = 0; i<2; ++i)
	{
		retval = recv(client_sock[i], buf, sizeof(len), 0);			//�غ�Ϸ� �޼��� ����.
		if (retval == SOCKET_ERROR)
		{
			err_display("recv()");
		}
	}
	
	
	//send - �������� �Ѿ��� �޼��� ����

	//ResumeThread ���ֱ����� ���� �ʱⰪ�� �������ְ� �����غ�Ϸ� �Ǹ� ResumeThread ���ش�.
	ResumeThread(hThreadHandle[0]);
	ResumeThread(hThreadHandle[1]);

	WaitForMultipleObjects(2,hThreadHandle,TRUE,INFINITE);
}

CThreadManager::~CThreadManager()
{}
