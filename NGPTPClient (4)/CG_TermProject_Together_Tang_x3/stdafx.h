// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once
#pragma comment(lib,"winmm") 
#pragma comment(lib, "ws2_32")

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


//#define SERVERIP "192.168.80.62"
//#define SERVERIP "192.168.0.244"
//#define SERVERIP "192.168.83.243"
#define SERVERIP "127.0.0.1"

#define SERVERPORT	9595
#define BUFSIZE		512
// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

#include <gl\glew.h>
#include <gl\glut.h> 
#include <Winsock2.h>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <random>
#include <ctime>
#include <cmath>
#include <vector>
#include <mmsystem.h>

using namespace std;