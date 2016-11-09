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
	playerVector.push_back(PlayerInfo{ DataType::PLAYER,Vec3{ 1500,100,1900 },Vec3{ -1500,100,1900 },false });
	playerVector.push_back(PlayerInfo{ DataType::PLAYER,Vec3{ 1500,100,1900 },Vec3{ -1500,100,1900 },false });

	initInform1.Player1Pos = Vec3{ -1500, 100, 1900 };
	initInform1.Player2Pos = Vec3{ 1500, 100, 1900 };

	initInform2.Player1Pos = Vec3{ -1500, 100, 1900 };
	initInform2.Player2Pos = Vec3{ 1500, 100, 1900 };
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
