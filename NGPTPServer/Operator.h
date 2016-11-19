#pragma once
#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <iostream>
#include <vector>
#include "Protocol.h"

#define BUFSIZE 512

class COperator
{
public:
	COperator();
	COperator(std::vector<PlayerInfo>*, std::vector<MonsterInfo> *, std::vector<BulletInfo> *);
	~COperator();
	void Update();				// recv, send 이루어지는데 지금 하려던대로 하면 잘 안될것 같음.	
								// 아마 처리해야할 함수별? 작업별로 스레드로 다중 처리 해줘야 할듯.
	void MonsterPosUpdate();	// 몬스터들의 위치를 실시간으로 움직여줌. 정의만해놈, CThreadMgr 로 뻈음.
	void PlayerPosUpdate();		// 플레이어 위치 실시간 동기화
	void BulletPosUpdate();

	//----충돌 함수들--
	bool CollisionBulletWithMonster(BulletInfo&, MonsterInfo&);								// 총알하고 몬스터 충돌함수
	bool CollisionBulletWithMap(BulletInfo&);				// 맵전체하고 총알
	bool CollisionBulletWithObstacle(BulletInfo&bullet, ContainerInfo& container);			// 총알하고 장애물 충돌함수
	bool CollisionObstacleWithPlayer(PlayerInfo&,ContainerInfo&);			// 장애물과 플레이어 충돌함수
	

	
private:
	static std::vector<PlayerInfo>  * playerVecForCalcul;		// Player정보 관리 배열. Maxsize = 2.
	static std::vector<MonsterInfo> * monsterVecForCalcul;		// Monster정보 관리 배열. Maxsize = 10.
	static std::vector<BulletInfo> * bulletVecForCalcul;		// Bullet 정보 관리 배열. 클라로부터 생성 메세지를 받으면 
																// Insert해주고, 업데이트해줌.
	static std::vector<ContainerInfo> * conVecForCalcul;		// Container정보 관리 배열. 충돌체크에 사용된다.
	MapSizeInfo mapSizeInfo;									//맵 전체 크기, 충돌체크의 사용.	아직 안만듬.

	std::vector<PlayerInfo>::iterator playerIter;
	std::vector<MonsterInfo>::iterator monsterIter;
	std::vector<BulletInfo>::iterator bulletIter;

}; 