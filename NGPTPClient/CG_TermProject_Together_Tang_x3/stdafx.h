// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#pragma comment(lib,"winmm") 
#pragma comment(lib, "ws2_32")

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#define SERVERIP	"127.0.0.1" /*"192.168.83.243"*/
#define SERVERPORT	9000
#define BUFSIZE		512
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

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
