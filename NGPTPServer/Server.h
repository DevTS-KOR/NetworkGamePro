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
	SOCKADDR_IN server_addr;	// ���� ���� �ּ� ����ü
	SOCKADDR_IN client_addr;	// Ŭ�� ���� �ּ� ����ü
	SOCKET listen_sock;			// Listen Socket ����
	SOCKET client_sock[2];		// Ŭ���̾�Ʈ ���� ����
	int retval;					// return Value �� �޴� ����
	int m_ClientNum = 0;		// Ŭ�� � �����ߴ���
	int addrlen;				// �ּ� ����
};

