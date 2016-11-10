#pragma once
#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <iostream>
#include <vector>
#include "Protocol.h"
class COperator
{
public:
	COperator();
	COperator(std::vector<PlayerInfo>* );
	~COperator();
	void Update();			// recv, send 이루어지는데 지금 하려던대로 하면 잘 안될것 같음.	
							// 아마 처리해야할 함수별? 작업별로 스레드로 다중 처리 해줘야 할듯.
private:
	static std::vector<PlayerInfo>  * playerVecForCalcul;		// Player정보 관리 배열. Maxsize = 2.
	static std::vector<MonsterInfo>* monsterVecForCalcul;		// Monster정보 관리 배열. Maxsize = 10.
	static std::vector<BulletInfo> * bulletVecForCalcul;		// Bullet 정보 관리 배열. 클라로부터 생성 메세지를 받으면 
																// Insert해주고, 업데이트해줌.
	static std::vector<ContainerInfo> * conVecForCalcul;		// Container정보 관리 배열. 충돌체크에 사용된다.
	MapSizeInfo mapSizeInfo;									//맵 전체 크기, 충돌체크의 사용.	아직 안만듬.
};

