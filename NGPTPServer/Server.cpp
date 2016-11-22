#include "Server.h"

//#pragma comment(lib,"ws2_32")
CServer::CServer()
{
	//윈속 초기화 작업
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//Socket()
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET)
		err_quit("listen_sock()");

	//Bind()
	ZeroMemory(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR*)&server_addr, sizeof(server_addr));
	if (retval == SOCKET_ERROR)
		err_quit("Bind()");
}

void CServer::err_display(char * msg)
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
void CServer::err_quit(char * msg)
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

void CServer::Update()
{
	//listen
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
		err_quit("Listen()");
	/*hTempHandle = CreateThread(
		NULL, 0, CServer::tempThread, NULL, 0, NULL);*/
	while (true)
	{
		//Accept
		addrlen = sizeof(client_addr);
		client_sock[m_ClientNum] = accept(listen_sock, (SOCKADDR*)&client_addr, &addrlen);
		if (client_sock[m_ClientNum] == INVALID_SOCKET)
			err_quit("client_socket");
		printf("클라정보 : IP : %s, 포트번호 : %d \n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		if (m_ClientNum < 2)
			m_ClientNum++;
		if (m_ClientNum == 2)
			MakeThreadManager();
	}
}
void CServer::MakeThreadManager()
{
	CThreadManager threadMgr(client_sock[0],client_sock[1]);
	threadMgr.Update();
}

CServer::~CServer()
{
	closesocket(listen_sock);
	WSACleanup();
}
DWORD WINAPI CServer::tempThread(LPVOID param)
{
	int nextTime = 0;
	int leftTime = 1000 ;
	int nowTime;
	while (true)
	{
		
		nowTime = std::clock();
		if (nowTime > nextTime)
		{
			std::cout << "1" << std::endl;
			for (int i = 0; i < 100; ++i)
			{
				//std::cout << "샌드했음" << std::endl;
			}

			nextTime = std::clock() + leftTime;
			std::cout << "nowTime" << int(nowTime) << std::endl;
			/*	cout << "nextTime" << int(nextTime) << endl;
			cout << "leftTime" << int(leftTime) << endl;*/

		}
	}
}
