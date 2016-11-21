#include "Operator.h"
#pragma comment(lib, "ws2_32")

std::vector<PlayerInfo> * COperator::playerVecForCalcul;
std::vector<MonsterInfo>* COperator::monsterVecForCalcul;
std::vector<BulletInfo> * COperator::bulletVecForCalcul;
std::vector<ContainerInfo> * COperator::conVecForCalcul;
COperator::COperator(){}
COperator::COperator(
	std::vector<PlayerInfo>*  player, 
	std::vector<MonsterInfo> * monsters, 
	std::vector<BulletInfo> * bullets)
{
	playerVecForCalcul = player;
	monsterVecForCalcul = monsters;
	bulletVecForCalcul = bullets;

	playerIter = playerVecForCalcul->begin();
	monsterIter = monsterVecForCalcul->begin();
	//bulletIter = bulletVecForCalcul->begin();

}
void COperator::Update()		//recv������ ��� �ѱ��� ����ؾ��ҵ�.
{
	std::vector<PlayerInfo>::iterator iter;
	iter = playerVecForCalcul->begin();

	std::cout <<"player1"<< iter->PlayerPos.x << std::endl;
	++iter;
	std::cout << "player2" << iter->PlayerPos.x << std::endl;
}
void COperator::PlayerPosUpdate(PlayerInfo param)
{
	PlayerInfo a=param;
	std::cout << "playerposupdateȣ��" << std::endl;
	std::cout << a.playerIndex << std::endl;
	if (a.playerIndex == 1)
	{
		if (a.charKey == 'w')
		{
			std::cout << "wŰ��" << std::endl;
			playerIter->PlayerPos.x = 1;// 1��� recv������
		}
		if (a.charKey == 's')
		{

		}
		if (a.charKey == 'a')
		{

		}
		if (a.charKey == 'd')
		{

		}
	}
	else//a.playerIndex==2
	{
		++playerIter;
		playerIter->PlayerPos.x;
		--playerIter;
	}
}

bool COperator::CollisionBulletWithMonster(BulletInfo & bullet, MonsterInfo& monster)
{
	return(
		bullet.BulletPos.x+1 > monster.MonsterPos.x-30 &&
		bullet.BulletPos.x-1 < monster.MonsterPos.x+30 &&
		bullet.BulletPos.y+1 > monster.MonsterPos.y-55 &&
		bullet.BulletPos.y-1 < monster.MonsterPos.y+55 &&
		bullet.BulletPos.z+1 > monster.MonsterPos.z-15 &&
		bullet.BulletPos.z-1 < monster.MonsterPos.z+15
		);
}
bool COperator::CollisionBulletWithObstacle(BulletInfo&bullet, ContainerInfo& container )
{
	return(
		bullet.BulletPos.x + 1 > container.position.x - 128 &&
		bullet.BulletPos.x - 1 < container.position.x + 128 &&
		bullet.BulletPos.y + 1 > container.position.y - 128 &&
		bullet.BulletPos.y - 1 < container.position.y + 128 &&
		bullet.BulletPos.z + 1 > container.position.z - 256 &&
		bullet.BulletPos.z - 1 < container.position.z + 256
		);
}
bool COperator::CollisionBulletWithMap(BulletInfo& bullet)
{
	if (bullet.BulletPos.x + 1 > 2000)
		return true;
	if (bullet.BulletPos.x - 1 < -2000)
		return true;
	if (bullet.BulletPos.y + 1 > 2000)
		return true;
	if (bullet.BulletPos.y - 1 < -2000)
		return true;

	return false;
}
bool COperator::CollisionObstacleWithPlayer(PlayerInfo&player, ContainerInfo& container)
{
	return(
		player.PlayerPos.x + 1 > container.position.x - 128 &&
		player.PlayerPos.x - 1 < container.position.x + 128 &&
		player.PlayerPos.z + 1 > container.position.z - 256 &&
		player.PlayerPos.z - 1 < container.position.z + 256
		);
}
COperator::~COperator()
{

}
