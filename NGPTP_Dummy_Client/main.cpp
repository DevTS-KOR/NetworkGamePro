#pragma comment (lib,"ws2_32")
#include <WinSock2.h>
#include <stdlib.h>	
#include <iostream>
#include "protocol.h"
using namespace std;

#define SERVERIP "127.0.0.1"
//#define SERVERIP "10.30.1.6"
#define SERVERPORT 9000
#define BUFSIZE 512
SOCKET sock;
void err_quit(char * msg)
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
void err_display(char * msg)
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

int recvn(SOCKET s, char * buf, int len, int flags)
{
	int received;
	char * ptr = buf;
	int left = len;
	while (left > 0)
	{
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;

		else if (received == 0)
			break;

		left -= received;
		ptr += received;
	}
	return (len - left);
}


DWORD WINAPI ThreadFunc(LPVOID param)
{
	int retval;
	char buf[BUFSIZE];
	while(true)
	{
		retval = recv(sock, buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR)
		{
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;

		///받은 데이터 출력
		buf[retval] = '\0';
		printf("[tcp 클라이언트] %d 바이틀르 받았습니다. \n", retval);
		printf("[받은 데이터] %s \n", buf);

		InitInfo a;
		a = (InitInfo&)buf;
	}
	return 0;
}
int main(int argc, char * argv[])
{
	int retval;
	HANDLE handle;
	//윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	//socket

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
		err_quit("socket()");

	//connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect");

	//네트워크 사용 변수
	char buf[BUFSIZE + 1];
	int len;
	cout << "1" << endl;

	cout << "스레드 생성" << endl;
	handle = CreateThread(NULL, 0,ThreadFunc, NULL, 0, NULL);

	while (true)
	{
		cout << "2" << endl;
		//데이터 받기

		printf("\n [보낼 데이터] : ");
		if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
			break;

		// \n문자 제거
		len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strlen(buf) == 0)
			break;

		//데이터 보내기
		retval = send(sock, buf, strlen(buf), 0);
		if (retval == SOCKET_ERROR)
		{
			err_display("send()");
			break;
		}
		printf("[TCP 클라이언트] %d 바이트를 보냈습니다. \n", retval);
	}
	closesocket(sock);

	WSACleanup();
	return 0;
}