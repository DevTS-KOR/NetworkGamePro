#pragma once
#include "ThreadManager.h"
//#pragma comment(lib,"ws2_32")
#define SERVERPORT 9000

class CServer
{
public:
	CServer();
	~CServer();
	void err_quit(char * msg);
	void err_display(char * msg);
	void Update();
	void MakeThreadManager();
private:
	WSADATA wsaData;
	SOCKADDR_IN server_addr;	// 서버 소켓 주소 구조체
	SOCKADDR_IN client_addr;	// 클라 소켓 주소 구조체
	SOCKET listen_sock;			// Listen Socket 변수
	SOCKET client_sock[2];		// 클라이언트 소켓 변수
	int retval;					// return Value 값 받는 변수
	int m_ClientNum = 0;		// 클라 몇개 접속했는지
	int addrlen;				// 주소 길이
};

