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
	void Update();				// recv, send �̷�����µ� ���� �Ϸ������ �ϸ� �� �ȵɰ� ����.	
								// �Ƹ� ó���ؾ��� �Լ���? �۾����� ������� ���� ó�� ����� �ҵ�.
	void MonsterPosUpdate();	// ���͵��� ��ġ�� �ǽð����� ��������. 
	void PlayerPosUpdate();		// �÷��̾� ��ġ �ǽð� ����ȭ
	void BulletPosUpdate();

	//----�浹 �Լ���--
	void CollisionBulletWithMonster();	
	void CollisionObstacleWithPlayer();
	void CollisionBulletWithMap();
	void CollisionBulletWithObstacle();

	
private:
	static std::vector<PlayerInfo>  * playerVecForCalcul;		// Player���� ���� �迭. Maxsize = 2.
	static std::vector<MonsterInfo> * monsterVecForCalcul;		// Monster���� ���� �迭. Maxsize = 10.
	static std::vector<BulletInfo> * bulletVecForCalcul;		// Bullet ���� ���� �迭. Ŭ��κ��� ���� �޼����� ������ 
																// Insert���ְ�, ������Ʈ����.
	static std::vector<ContainerInfo> * conVecForCalcul;		// Container���� ���� �迭. �浹üũ�� ���ȴ�.
	MapSizeInfo mapSizeInfo;									//�� ��ü ũ��, �浹üũ�� ���.	���� �ȸ���.

}; 